# Board Design

## Pin usage

### Player 1

| PSoC Name | Description    | SNES Pin   | NES Pin   | PSoC Pin  |
| --------- | -------------- | ---------- | --------- | --------- |
| P1_D0     | Player 1 D0    | 4          | 4        | 1          |
| P1_D1     | Player 1 D1    | 3          | 6        | 66         |
| P1_D2     | Player 1 D2    | 2          | 7        | Unassigned |
| P1_Latch  | Player 1 Latch | 5          | 3        | 65         |
| P1_Clock  | Player 1 Clock | 6          | 2        | 62         |

### Player 2

| PSoC Name | Description    | SNES Pin   | NES Pin   | PSoC Pin  |
| --------- | -------------- | ---------- | --------- | --------- |
| P2_D0     | Player 2 D0    | 4          | 4        | 38         |
| P2_D1     | Player 2 D1    | 3          | 6        | 46         |
| P2_D2     | Player 2 D2    | 2          | 7        | Unassigned |
| P2_Latch  | Player 2 Latch | 5          | 3        | 47         |
| P2_Clock  | Player 2 Clock | 6          | 2        | 3          |
