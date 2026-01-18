# c-meadow-24

A small C tool that computes text statistics for meadow.

## Objective
- Provide quick text metrics for meadow documents.
- Report top word frequencies for fast inspection.

## Use cases
- Validate meadow drafts for repeated terms before review.
- Summarize meadow notes when preparing reports.

## Usage
cc main.c -o textstats && ./textstats data/sample.txt --top 5

## Output
- lines: total line count
- words: total word count
- chars: total character count
- top words: most frequent tokens (case-insensitive)

## Testing
- run `bash scripts/verify.sh`

## Notes
- Only ASCII letters and digits are treated as word characters.
