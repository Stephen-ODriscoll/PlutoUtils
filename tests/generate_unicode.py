import csv


def main(output_file):
    print(f'Generating {output_file}...')

    with open(output_file, mode='w', newline='', encoding='utf-8') as output:
        writer = csv.writer(output)

        writer.writerow(['Decimal', 'Code Point', 'UTF-8', 'UTF-16', 'UTF-32'])

        for i in range(0x110000):
            if 0xD7FF < i < 0xE000:
                continue

            try:
                char = chr(i)

                code_point = f'U+{i:04X}'

                utf8_bytes = char.encode('utf-8')
                utf16_bytes = char.encode('utf-16le')
                utf32_bytes = char.encode('utf-32le')

                utf8_hex = ' '.join(f'{byte:02X}' for byte in utf8_bytes)
                utf16_hex = ' '.join(f'{byte:02X}' for byte in utf16_bytes)
                utf32_hex = ' '.join(f'{byte:02X}' for byte in utf32_bytes)

                writer.writerow([i, code_point, utf8_hex, utf16_hex, utf32_hex])

            except ValueError:
                print(f'Failed to get encodings for {i}')
                continue

    print('Generation complete!')


if __name__ == '__main__':
    main('unicode.csv')
