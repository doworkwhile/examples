#ifndef LINE_LIST_FILE_OPS
#define LINE_LIST_FILE_OPS

void LineListFileOps_Write(LineList* l, char* filename)
{
	FILE* fp = fopen(filename, "w+");
	int lineLen = l->width;
	// len must be 1 larger to accomodate
	char writeLine[lineLen + 1];

	for (int i = 0; i < l->lines; i++) {
		char* curWrite = l->store[i]->contents;

		// copy the line, because...
		for (int j = 0; j < lineLen; j++) {
			writeLine[j] = curWrite[j];
		}
		writeLine[lineLen] = '\0';

		// we need to set the last empty char to a string ending char
		for (int j = lineLen - 2; j >= 0; j--) {
			if (writeLine[j] == ' ') {
				writeLine[j] = '\0';
			} else {
				break;
			}
		}

		long unsigned int realLen = strlen(&writeLine[0]);
		if (realLen > 0) {
			fputs(writeLine, fp);
			fputs("\n", fp);
		}
	}
	fclose(fp);
}


void LineListFileOps_Load(LineList* l, char* filename)
{
	FILE* fp = fopen(filename, "a+");
	if (fp == NULL) {
		printf("File could not be opened\n");
		exit(0);
	}

	int maxLineLen = l->width;
	char readBuf[maxLineLen + 1];
	memset(readBuf, 0, maxLineLen + 1);
	int curBuf = 0;
	int curLine = 0;

	char ch = getc(fp);
	while (ch != EOF) {

		if (curBuf < maxLineLen && ch != '\n') {
			readBuf[curBuf] = ch;
			curBuf++;
		} else if (curBuf > 0 && ch == '\n' && curLine < l->lines) {
			readBuf[maxLineLen] = '\0';
			for (int i = 0; i <= maxLineLen; i++) {
				l->store[curLine]->contents[i] = readBuf[i];
			}
			memset(readBuf, 0, maxLineLen + 1);
			curBuf = 0;
			curLine++;
		}

		ch = getc(fp);
	}
	readBuf[maxLineLen] = '\0';

	fclose(fp);
}

#endif