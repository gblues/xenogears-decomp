import math
import mmap
import yaml
import psx.lzss as lzss

from cdrom.cdxa import CdromXa

"""
Parses a YAML file into Overlay objects that can be fed into OverlayExtractor.extract()

The YAML is expected to have the following structure:

---
overlays:
  compressed:
  - name: some_name
    sector_id: 0x00 
  uncompressed:
  - name: some_name
    sector_id: 0x00
    index: 0x00
"""
def parse_yaml(yaml_file: str):
    with open(yaml_file) as fh:
        spec = yaml.safe_load(fh)

    if 'overlays' not in spec:
        raise ValueError("Invalid yaml: top level key 'overlays' not found")
    overlays = spec['overlays']

    compressed = overlays['compressed'] if 'compressed' in overlays else []
    uncompressed = overlays['uncompressed'] if 'uncompressed' in overlays else []

    return [Overlay(name=x["name"], sector_id=x["sector_id"]) for x in compressed] + [Overlay(name=x["name"], sector_id=x["sector_id"], index=x["index"]) for x in uncompressed]

class Overlay(object):
    def __init__(self, name: str, sector_id: int, index: int=-1):
        self.compressed = index < 0
        self.name = name
        self.index = index
        self.sector_id = sector_id


class OverlayExtractor(object):
    def __init__(self, disc: CdromXa):
        header = disc.read_sector(0x28)
        disc.seek_sector(0x18)
        table = b''
        for i in range(0x10):
            table += disc.read_next_sector()
        self.header = header
        self.table = table
        self.current_decoding_value = 0
        self.disc = disc

    def __set_decoding_value(self, nybble_index, offset=0):
        byte_offset = offset + (nybble_index * 2)
        lsb, msb = self.header[byte_offset:byte_offset+2]
        self.current_decoding_value = (msb << 8) + lsb - 1


    def __get_sector(self, index):
        offset = self.__index_to_offset(index)
        sector = self.table[offset]
        sector += (self.table[offset + 1] * 0x100)
        sector += (self.table[offset + 2] * 0x10000)
        return sector


    def __get_size(self, index):
        offset = self.__index_to_offset(index)
        size = (self.table[offset + 6] * 0x1000000)
        size += (self.table[offset + 5] * 0x10000)
        size += (self.table[offset + 4] * 0x100)
        size += self.table[offset + 3]
        return size

    def __index_to_offset(self, index):
        return (index + self.current_decoding_value - 1) * 7

    def extract(self, overlay: Overlay, output_dir='.'):
        if overlay.compressed:
            self.__extract_compressed_overlay(overlay, output_dir)
        else:
            self.__extract_overlay(overlay, output_dir)

    def __extract_overlay(self, overlay: Overlay, output_dir: str):
        self.__set_decoding_value(overlay.index)
        sector = self.__get_sector(overlay.sector_id)
        size = self.__get_size_aligned(overlay.sector_id)
        file_path = output_dir + "/" + overlay.name
        with open(file_path, "wb") as fh:
            self.disc.extract_sectors(sector, size, fh)

    def __extract_compressed_overlay(self, overlay: Overlay, output_dir: str):
        self.__set_decoding_value(1)
        sector = self.__get_sector(overlay.sector_id)
        size = math.ceil(self.__get_size_aligned(overlay.sector_id) / CdromXa.SECTOR_DATA_SIZE) * CdromXa.SECTOR_DATA_SIZE
        file_path = output_dir + "/" + overlay.name

        with mmap.mmap(-1, size) as compressed:
            self.disc.extract_sectors(sector, size, compressed)
            compressed.seek(0)
            with open(file_path, "+wb") as uncompressed:
                lzss.decompress(compressed, uncompressed)

    def __get_size_aligned(self, index):
        size = self.__get_size(index)
        v = size + 3
        if v < 0:
            v = size + 6
        return (v >> 2) << 2

