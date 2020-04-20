THIS IS USED IN PIKMIN 1 ONLY


# Header

| Offset | Size | Description |
| ------ | ---- | ----------- |
| 0x00   | 4    | Number of structs |

# Mock-directory struct

| Offset 			  | Size | Description |
| ------------------- | ---- | ----------- |
| 0x00  			  | 4    | *File content indicator |
| 0x04  			  | 4    | Enclosed file size |
| 0x08   			  | 4    | Mock-directory string length |
| 0x0C   			  | *8Val| Mock-directory path |
| 0x0c + 0x08 value   | *4Val| Enclosed file |

*8Val = 0x08 value
*4Val = 0x04 value

# File content indicators

| Type | Number |
| ---- | ------ |
| PCR  | 0 |
| BTI  | 1 |
| DCA  | 2 |
| DCK  | 3 |
