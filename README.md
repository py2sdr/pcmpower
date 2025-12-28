<img width="739" height="484" alt="Screenshot_2025-12-28_16-13-18" src="https://github.com/user-attachments/assets/ac23f523-f0cb-4419-9cd9-048118bc2b4a" />


# pcmpwr

A real-time PCM audio power monitor that calculates and displays the power level of audio data in decibels.

## Description

`pcmpwr` reads 16-bit signed PCM audio data from standard input, processes it in blocks, and outputs timestamped power measurements in decibels. This tool is useful for monitoring audio signal strength in real-time processing pipelines.

### Features

- Reads 16-bit signed integer PCM audio data
- Calculates power in decibels
- Outputs measurements with sub-second precision timestamps
- Configurable timestamp format (deciseconds or milliseconds)
- Processes audio in efficient 8192-sample blocks

## Compiling

To compile the program, use the following command:

```bash
gcc -Wall -Wextra -std=c11 -O2 pcmpwr.c -o pcmpwr -lm
```

This compiles with:
- `-Wall -Wextra`: Enable all warnings
- `-std=c11`: Use C11 standard
- `-O2`: Optimization level 2
- `-lm`: Link against the math library (required for `log10`)

## Usage

```bash
pcmpwr < audio_input.raw
```

Or in a pipeline:

```bash
sdr_audio_source | pcmpwr
```

### Output Format

Each line of output follows this format:

```
YYYY-MM-DD HH:MM:SS.D -- XX.X dB
```

Example:
```
2025-12-28 14:23:45.3 -- -33.5 dB
2025-12-28 14:23:45.4 -- -33.2 dB
```

## Configuration

### Block Size

The default block size is 8192 samples. You can adjust this by changing the `BLOCK_SIZE` definition at the top of the source file.

## Input Format

- **Sample format**: 16-bit signed integer (int16_t)
- **Byte order**: Native system endianness
- **Channels**: Mono only

## Notes

- The program handles `-INFINITY` dB for signals with mean square power less than 1.0
- Error handling is included for read failures
- Output is flushed after each measurement for real-time monitoring

## License

[MIT License](https://opensource.org/licenses/MIT)
