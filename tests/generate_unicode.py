import csv


def main(output_file):
    print(f'Generating {output_file}...')

    with open(output_file, mode='w', newline='', encoding='utf-8') as output:
        writer = csv.writer(output)

        writer.writerow(['Decimal', 'Code Point', 'UTF-8', 'UTF-16BE', 'UTF-32BE'])

        for i in range(0x110000):
            if 0xD7FF < i < 0xE000:
                continue

            try:
                char = chr(i)

                code_point = f'U+{i:04X}'

                utf8_bytes = char.encode('utf-8')
                utf16be_bytes = char.encode('utf-16be')
                utf32be_bytes = char.encode('utf-32be')

                utf8_hex = ' '.join(f'{byte:02X}' for byte in utf8_bytes)
                utf16be_hex = ' '.join(f'{byte:02X}' for byte in utf16be_bytes)
                utf32be_hex = ' '.join(f'{byte:02X}' for byte in utf32be_bytes)

                writer.writerow([i, code_point, utf8_hex, utf16be_hex, utf32be_hex])

            except ValueError:
                print(f'Failed to get encodings for {i}')
                continue

    print('Generation complete!')


if __name__ == '__main__':
    main('unicode.csv')
