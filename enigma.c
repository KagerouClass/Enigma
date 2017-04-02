//************programmer:TSAI Chan-Chang≤Ã’πË∞******************//
//***********************ID:3150105426******************************//
#include<stdio.h>
#include<string.h>
char rotorTable[5][27] =
{
	"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
	"ESOVPZJAYQUIRHXLNFTGKDCMWB",
	"VZBRGITYUPSDNHLXAWMJQOFECK"
};
char reflector[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
char stepChar[5] = "RFWKA"; // Royal Flags Wave Kings Above
char plugBoard[] = "ZNVDEFTYKUILPBOMWRXGJCQSHA";
int rotorNum[3] = { 5, 3, 2 };//rotor¢Û 22->23                 rotor¢Ú 5->6 
char ringSetting[3] = { 'W', 'E', 'B'};
char messageKey[3];
char *enigma_encrypt_decrypt(char *p);
int main()
{
	char *cipher = "SWJYPKBDSVSYSJPYXKSDGHFRPZUDWYPBWJXOMZOPBYYKUKGDTJOEFUBAZDBDVXKWRAKOHGSKXVGYFGVAGLCQ";
	char *plainText;
	int i, j, k;
	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			for (k = 0; k < 26; k++)
			{
				messageKey[0] = i + 'A';
				messageKey[1] = j + 'A';
				messageKey[2] = k + 'A';
				plainText = enigma_encrypt_decrypt(cipher);
				if (strstr(plainText, "HITLER"))
				{
					printf("MessageKey=%c%c%c\n",i + 'A', j + 'A', k + 'A');
					printf("PlainText=");
					printf("%s\n", plainText);
					break;
				}
			}
		}
	}
	getchar();
	return 0;
}
char *enigma_encrypt_decrypt(char *cipher)
{
	char plainText[1000] = { 0 };
	int plain = 0;
	int delta5 = 0;
	int delta3 = 0;
	int delta2 = 0;
	int count = 0;
	char temp;
	delta5 = messageKey[0] - ringSetting[0];
	delta3 = messageKey[1] - ringSetting[1];
	delta2 = messageKey[2] - ringSetting[2];

	while (*cipher != '\0')
	{
		messageKey[2] += 1;
		if (messageKey[2] == 'Z' + 1) messageKey[2] = 'A';
		if (messageKey[2] == 'F')//the middle rottor is been rotated
		{
			if (messageKey[1] == 'V')//all rotors rotate
			{
				messageKey[1] += 1;
				messageKey[0] += 1;
				if (messageKey[1] == 'Z' + 1) messageKey[1] = 'A';
				if (messageKey[0] == 'Z' + 1) messageKey[0] = 'A';
			}
			else
			{
				messageKey[1] += 1;
				if (messageKey[1] == 'Z' + 1) messageKey[1] = 'A';
			}
		}
		else if (messageKey[1] == 'V')//double rotation
		{
			messageKey[1] += 1;
			messageKey[0] += 1;
			if (messageKey[1] == 'Z' + 1) messageKey[1] = 'A';
			if (messageKey[0] == 'Z' + 1) messageKey[0] = 'A';
		}
		temp = *cipher;
		///////////////////rotation first//////////////////////////
		//right to  left
		//plugboard
		temp = plugBoard[temp - 'A'];
		//rotor II
		temp = (rotorTable[1][((temp - 'A') + messageKey[2] - ringSetting[2] + 26) % 26] - 'A' - messageKey[2] + ringSetting[2] + 26) % 26 + 'A';
		//rotor ¢Û
		temp = (rotorTable[2][((temp - 'A') + messageKey[1] - ringSetting[1] + 26) % 26] - 'A' - messageKey[1] + ringSetting[1] + 26) % 26 + 'A';
		//rotor ¢ı
		temp = (rotorTable[4][((temp - 'A') + messageKey[0] - ringSetting[0] + 26) % 26] - 'A' - messageKey[0] + ringSetting[0] + 26) % 26 + 'A';
		//reflector
		temp = reflector[temp - 'A'];
		//rotor ¢ı
		for (count = 0; rotorTable[4][count] != (temp - 'A' + messageKey[0] - ringSetting[0] + 26) % 26 + 'A'; count++);
		temp = ((count - messageKey[0] + ringSetting[0]) + 26) % 26 + 'A';
		//rotor ¢Û
		for (count = 0; rotorTable[2][count] != (temp - 'A' + messageKey[1] - ringSetting[1] + 26) % 26 + 'A'; count++);
		temp = ((count - messageKey[1] + ringSetting[1]) + 26) % 26 + 'A';
		//rotor II
		for (count = 0; rotorTable[1][count] != (temp - 'A' + messageKey[2] - ringSetting[2] + 26) % 26 + 'A'; count++);
		temp = ((count - messageKey[2] + ringSetting[2]) + 26) % 26 + 'A';

		for (count = 0; plugBoard[count] != temp; count++);
		temp = count + 'A';
		plainText[plain] = temp;
		plain++;
		cipher++;
	}
	return plainText;
}