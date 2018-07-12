#include "font.h"
#include "FontData.h"
#include "memory.h"
#include "stdint.h"

char hankaku[4096];

char LoadFontFromMemory()
{
	unsigned char* buffer = (unsigned char*)hankaku;
	int bufferIndex = 0;
	int charIndex = 0;

	memset(buffer, 0, 4096);

	int readIndex = 0;

	//fontData�� ���ǵ� ��Ʈ �迭�� Ŀ�ο��� ����� �� �ֵ��� ��ȯ�ؼ� skyFontData�� �����Ѵ�.
	//��Ʈ ������ 255��, �� ��Ʈ�� 8 * 16 = 128����Ʈ�̹Ƿ� fontData �迭�� ũ��� 32768
	while (readIndex < 32768) {

		//�ѹ��ڸ� ǥ���ϴ� ��Ʈ�� 8 * 16 = 128����Ʈ
		for (int i = 0; i < 128; i++)
		{
			//'*'�� �ȼ���, '.'�� �� ������ �ǹ��Ѵ�.
			//fontdata���� �ѹ����� ���� �� ������ 8����Ʈ�̹Ƿ�
			//�� 8����Ʈ�� �����鼭 1����Ʈ ������ ��´�.
			//skyFontData�� 4096 ����Ʈ �迭�̴�. => 32768 / 8 = 4096
			if (fontData[readIndex + i] == '*')
			{

				if (charIndex < 8)
				{
					char a = (char)(1 << (8 - 1 - charIndex));
					buffer[bufferIndex] |= a;
				}

			}

			if ((fontData[readIndex + i] == '*') || (fontData[readIndex + i] == '.'))
			{
				charIndex++;

				if (charIndex >= 8)
				{
					//8����Ʈ�� üũ�����Ƿ� bufferIndex�� �ϳ� ������Ų��.
					bufferIndex++;
					charIndex = 0;
				}
			}
		}

		readIndex += 128;

	}

	return 1;
}