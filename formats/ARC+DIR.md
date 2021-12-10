THIS IS USED IN PIKMIN 1 ONLY


# Header

| Offset | Size | Description |
| ------ | ---- | ----------- |
| 0x00   | 4    | Size of DIR file |
| 0x04   | 4    | Number of structs |

# Mock-directory struct

| Offset | Size | Description |
| ------ | ---- | ----------- |
| 0x00   | 4    | Offset of file in ARC |
| 0x04   | 4    | Size of file in ARC |
| 0x08   | 4    | Mock-directory string length |
| 0x0C   | 4    | Mock-directory path |