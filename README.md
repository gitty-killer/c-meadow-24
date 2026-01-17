# c-meadow-24

A small C tool that computes text statistics for meadow.

## Goal
- Provide quick text metrics for meadow documents.
- Report top word frequencies for fast inspection.

## Usage
cc main.c -o textstats && ./textstats data/sample.txt --top 5

## Output
- lines: total line count
- words: total word count
- chars: total character count
- top words: most frequent tokens (case-insensitive)

## Notes
- Only ASCII letters and digits are treated as word characters.
