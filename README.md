<img width="739" height="484" alt="Screenshot_2025-12-28_16-18-22" src="https://github.com/user-attachments/assets/7f525172-f08a-4a9b-b2ad-1b56d1e76668" />

# pcmpwr

A real-time PCM audio power monitor that calculates and displays the power level of audio data in decibels.

## Description

`pcmpwr` reads 16-bit signed PCM audio data from standard input, processes it in blocks, and outputs timestamped power measurements in decibels. This tool is useful for monitoring audio signal strength in real-time processing pipelines.

## Features

- Reads 16-bit signed integer PCM audio data
- Calculates power in decibels
- Outputs measurements with sub-second precision timestamps
- Configurable timestamp format (deciseconds or milliseconds)
- Processes audio in efficient 8192-sample blocks

## Mathematical Foundation
For a discrete buffer of $N$ samples, the power is calculated as:

$$P_{dB} = 10 \cdot \log_{10} \left( \frac{1}{N} \sum_{i=1}^{N} s_i^2 \right)$$

Where:
* $s_i$ is the individual 16-bit signed PCM sample.
* $s_i^2$ represents the instantaneous power of that sample.
* $\frac{1}{N} \sum s_i^2$ is the average power (Mean Square) over the window $N$.

## Compiling

To compile the program, use the following command:

```bash
gcc -Wall -Wextra -std=c11 -O2 pcmpwr.c -o pcmpwr -lm
```

## Usage

```bash
pcmpwr < audio_input.raw
```

Or in a pipeline:

```bash
sdr_audio_source | pcmpwr
```

## Notes

### Block Size

The default block size is 8192 samples. You can adjust this by changing the `BLOCK_SIZE` definition at the top of the source file.

### Input Format

- **Sample format**: 16-bit signed integer (int16_t)
- **Byte order**: Native system endianness
- **Channels**: Mono only

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

## License

[MIT License](https://opensource.org/licenses/MIT)
