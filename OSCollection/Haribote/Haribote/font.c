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

	//fontData에 정의된 폰트 배열을 커널에서 사용할 수 있도록 변환해서 skyFontData에 저장한다.
	//폰트 개수는 255개, 한 폰트는 8 * 16 = 128바이트이므로 fontData 배열의 크기는 32768
	while (readIndex < 32768) {

		//한문자를 표현하는 폰트는 8 * 16 = 128바이트
		for (int i = 0; i < 128; i++)
		{
			//'*'는 픽셀을, '.'은 빈 공간을 의미한다.
			//fontdata에서 한문자의 가로 한 라인은 8바이트이므로
			//이 8바이트를 읽으면서 1바이트 공간에 담는다.
			//skyFontData는 4096 바이트 배열이다. => 32768 / 8 = 4096
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
					//8바이트를 체크했으므로 bufferIndex를 하나 증가시킨다.
					bufferIndex++;
					charIndex = 0;
				}
			}
		}

		readIndex += 128;

	}

	return 1;
}
