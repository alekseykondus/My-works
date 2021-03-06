#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <direct.h> 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

struct user
{
	unsigned long long int id;
	int role;
	char log_pass[20];
};
struct book
{
	int id;
	int number;
	char name[50];
	char writer[20];
};

void out_BLUE_RED(const char str[100])
{
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_RED);
	cout << str << endl;
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
void out_RED(const char str[100])
{
	SetConsoleTextAttribute(console, FOREGROUND_RED);
	cout << str << endl;
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
void out_GREEN(const char str[100])
{
	SetConsoleTextAttribute(console, FOREGROUND_GREEN);
	cout << str << endl;
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
int input_bool_1_0(char(&a)[100])
{
	if (a[0] == 48)
		return 0;
	else if (a[0] == 49)
		return 1;
	else
	{
		out_RED("Номер функции введен не правильно!");
		return -1;
	}
}
int input1_2(char(&a)[100])
{
	if (a[0] == 49)
		return 1;
	else if (a[0] == 50)
		return 2;
	else
	{
		out_RED("Номер функции введен не правильно!");
		return 0;
	}
}

int input1_2_3(char(&a)[100])
{
	if (a[0] == 49)
		return 1;
	else if (a[0] == 50)
		return 2;
	else if (a[0] == 51)
		return 3;
	else
	{
		out_RED("Номер функции введен не правильно!");
		return 0;
	}
}
int input1_2_3_4(char(&a)[100])
{
	if (a[0] == 49)
		return 1;
	else if (a[0] == 50)
		return 2;
	else if (a[0] == 51)
		return 3;
	else if (a[0] == 52)
		return 4;
	else
	{
		out_RED("Номер функции введен не правильно!");
		return 0;
	}
}

bool b1(char* mas1, char* mas2, int n)
{
	for (int i = 0; i < n; i++)
		if (mas1[i] != mas2[i])
			return 0;
	return 1;
}
void logpass(char(&login)[20], char(&password)[20], user& client)
{
	for (int i = 0; i < size(client.log_pass); i++)
		client.log_pass[i] = login[i] * password[i];
}
bool b_keys(user& client)
{
	FILE* keys;

	if (fopen_s(&keys, "data1", "rb"))
		perror("Error");
	else
	{
		user client2;
		while (!feof(keys))
		{
			fread(&client2, sizeof(user), 1, keys);
			if (feof(keys))
				break;
			if (b1(client2.log_pass, client.log_pass, size(client.log_pass)))
			{
				fclose(keys);
				client = client2;
				return 1;
			}
		}
	}
	fclose(keys);
	return 0;
}

void createPerson(user& client)
{
	while (1)
	{
		char login[20], password[20];
		cout << "Создайте логин: ";
		cin >> login;
		cout << "Создайте пароль: ";
		cin >> password;
		cout << endl;
		logpass(login, password, client);

		if (!b_keys(client))
		{
			cout << "1 - user" << endl << "2 - admin" << endl << "_____________" << endl;
			cout << "Введите роль: ";
			char a[100];
			cin >> a;
			client.role = input1_2(a);

			if (client.role != 1 && client.role != 2)
				out_RED("Роль введена не правильно!");
			else
			{
				if (client.role == 2)
					while (1)
					{
						char* a = new char[4];
						char b[] = "0000";
						cout << "Введите пароль: ";
						cin >> a;
						if (b1(a, b, 4))
						{
							break;
						}
					}
				FILE* keys;
				if (fopen_s(&keys, "data1", "rb"))
					perror("Error");
				else
				{
					user client2;
					client2.id = 0;
					while (!feof(keys))
					{
						fread(&client2, sizeof(user), 1, keys);
						if (feof(keys))
							break;
					}
					fclose(keys);
					client.id = client2.id + 1;
					cout << "Ваш ID: " << client.id << endl;
					if (fopen_s(&keys, "data1", "a+b"))
						perror("Error");
					else
					{
						fwrite(&client, sizeof(user), 1, keys);
						fclose(keys);
					}
					if (b_keys(client))
					{
						out_GREEN("Вы успешно зарегистририровались");
						break;
					}
				}
			}
		}
		else
			out_BLUE_RED("Пользователь с таким логином и паролем уже существует, выбирете другой");
	}
}

bool b_library(book& str) //проверяет наличие книги в библиотеке
{
	FILE* library;
	if (fopen_s(&library, "library", "rb"))
		perror("Error");
	else
	{
		book str2;
		while (!feof(library))
		{
			fread(&str2, sizeof(book), 1, library);

			if (b1(str.name, str2.name, size(str.name)) && b1(str.writer, str2.writer, size(str.writer)))
			{
				str = str2;
				fclose(library);
				return 1;
			}
		}
	}
	fclose(library);
	return 0;
}

void book_search_nameandwriter(book& str)
{
	FILE* library;
	bool b = 0;
	if (fopen_s(&library, "library", "rb"))
		perror("Error");
	else
	{
		book str2;
		while (!feof(library))
		{
			fread(&str2, sizeof(book), 1, library);
			if (b1(str.name, str2.name, size(str.name)) && b1(str.writer, str2.writer, size(str.writer)))
			{
				cout << endl << "ID: " << str2.id << endl << "Количество: " << str2.number << endl;
				cout << "Название книги: " << str2.name << endl << "Автор: " << str2.writer << endl;
				b = 1;
				break;
			}
		}

		if (!b)
			out_BLUE_RED("Такой книги нет в наличии");
		fclose(library);
	}
}

bool book_search_id(book& str)
{
	FILE* library;
	bool b = 0;
	if (fopen_s(&library, "library", "rb"))
		perror("Error");
	else
	{
		book str2;
		while (!feof(library))
		{
			fread(&str2, sizeof(book), 1, library);
			if (str.id == str2.id)
			{
				str = str2;
				cout << endl << "ID: " << str2.id << endl << "Количество: " << str2.number << endl;
				cout << "Название книги: " << str2.name << endl << "Автор: " << str2.writer << endl;
				b = 1;
				fclose(library);
				return 1;
			}
		}
		if (!b)
			out_BLUE_RED("Такой книги нет в наличии");
	}
	fclose(library);
	return 0;
}

void book_registration()
{
	book registration;
	cout << "Введите название книги: ";
	cout << endl;
	cin >> registration.name;
	cout << "Введите автора: ";
	cin >> registration.writer;
	cout << "Введите количество книг: ";
	cin >> registration.number;

	if (!b_library(registration))
	{
		FILE* library1;
		if (fopen_s(&library1, "library", "rb"))
			perror("Error");
		else
		{
			book str1;
			str1.id = 0;
			while (!feof(library1))
			{
				fread(&str1, sizeof(book), 1, library1);
				if (feof(library1))
					break;
			}
			registration.id = str1.id + 1;
			cout << "ID: " << registration.id << endl;
			fclose(library1);
			FILE* library2;
			if (fopen_s(&library2, "library", "a+b"))
				perror("Error");
			else
				fwrite(&registration, sizeof(book), 1, library2);
			fclose(library2);
		}
	}
	else
		out_BLUE_RED("Такая книга уже есть в наличии");
}

void book_delete()
{
	book b_delete;
	bool b = 0;
	while (!b)
	{
		cout << "Введите ID: ";
		cin >> b_delete.id;

		FILE* library1;
		FILE* library2;

		if (book_search_id(b_delete))
		{
			cout << endl << "Вы точно хотите безвозвратно удалить эту книгу?" << endl;
			cout << "1 - Да" << endl << "0 - Нет" << endl << "_______" << endl;
			cin >> b;
			if (b)
			{
				if (fopen_s(&library1, "library", "rb") || fopen_s(&library2, "library_copy", "wb"))
					perror("Error");
				else
				{
					book str;
					while (!feof(library1))
					{
						fread(&str, sizeof(book), 1, library1);
						if (feof(library1))
							break;
						fwrite(&str, sizeof(book), 1, library2);
					}
					fclose(library1);
					fclose(library2);
				}

				if (fopen_s(&library1, "library", "wb") || fopen_s(&library2, "library_copy", "rb"))
					perror("Error");
				else
				{
					book str;
					while (!feof(library2))
					{
						fread(&str, sizeof(book), 1, library2);
						if (feof(library2))
							break;
						if (str.id != b_delete.id)	fwrite(&str, sizeof(book), 1, library1);
					}
					fclose(library1);
					fclose(library2);
				}

				if (!b_library(b_delete))
					out_GREEN("Книга успешно удалена");
				break;
			}
		}
	}
	remove("library_copy");
}

void  book_edit(book& b_ch, int b) //редактируем информацию о книге
{

	FILE* library1;
	FILE* library2;

	if (fopen_s(&library1, "library", "rb") || fopen_s(&library2, "library_copy", "wb"))
		perror("Error");
	else
	{
		book str;
		while (!feof(library1))
		{
			fread(&str, sizeof(book), 1, library1);
			if (feof(library1))
				break;
			if (str.id == b_ch.id)
			{
				switch (b)
				{
				case 1:
					for (int i = 0; i < size(b_ch.name); i++)
						str.name[i] = b_ch.name[i];
					break;
				case 2:
					for (int i = 0; i < size(b_ch.name); i++)
						str.writer[i] = b_ch.writer[i];
					break;
				case 3:
					str.number = b_ch.number;
					break;
				}
			}
			fwrite(&str, sizeof(book), 1, library2);
		}
		fclose(library1);
		fclose(library2);
	}

	if (fopen_s(&library1, "library", "wb") || fopen_s(&library2, "library_copy", "rb"))
		perror("Error");
	else
	{
		book str;
		while (!feof(library2))
		{
			fread(&str, sizeof(book), 1, library2);
			if (feof(library2))
				break;
			fwrite(&str, sizeof(book), 1, library1);
		}
		fclose(library1);
		fclose(library2);
	}
	remove("library_copy");
}


void user_book_add(user& client, book& str) //вписывать в файл информацию о книге, которую взял пользователь
{
	_mkdir("users");

	char a[100] = "users\\";

	int id_copy = client.id, z = 0;
	while (id_copy != 0)
	{
		id_copy /= 10;
		z++;
	}
	//char *client_id_char = new char [z];
	id_copy = client.id;
	cout << client.id << endl;

	char* client_id_char = new char[z];
	//cout << client.id << endl;

	sprintf_s(client_id_char, sizeof(client_id_char), "%d", id_copy);
	//cout << client.id << endl;

	//cout << "ID: " << client.id << endl << "ID_char: " << client_id_char << endl;
	strcat_s(a, client_id_char);
	//cout << str.name << ' ' << str.writer << ' ' << str.id << endl;
	FILE* b_user;
	if (fopen_s(&b_user, a, "a+b"))
		perror("Error");
	else
		fwrite(&str, sizeof(book), 1, b_user);
	fclose(b_user);
}

bool user_book_check(user& client, book& str) //при возврате книги проверяет, есть ли такая книга у пользователя
{
	_mkdir("users");
	char a[100] = "users\\";

	int id_copy = client.id, z = 0;
	while (id_copy != 0)
	{
		id_copy /= 10;
		z++;
	}
	id_copy = client.id;
	char* client_id_char = new char[z];
	sprintf_s(client_id_char, sizeof(client_id_char), "%d", id_copy);
	strcat_s(a, client_id_char);

	FILE* b_user1;
	FILE* b_user2;
	book str1;
	if (fopen_s(&b_user1, a, "rb"))
		perror("Error");
	else
	{
		while (!feof(b_user1))
		{
			fread(&str1, sizeof(book), 1, b_user1);
			if (feof(b_user1))
				break;
			if (b1(str.name, str1.name, size(str.name)) && b1(str.writer, str1.writer, size(str.writer)))
			{
				fclose(b_user1);

				char b[100] = "users\\";
				char c[] = "_copy";
				strcat_s(b, client_id_char);
				strcat_s(b, c);

				if (fopen_s(&b_user1, a, "rb") || fopen_s(&b_user2, b, "wb"))
					perror("Error");
				else
				{
					book str1;
					while (!feof(b_user1))
					{
						fread(&str1, sizeof(book), 1, b_user1);
						if (feof(b_user1))
							break;
						fwrite(&str1, sizeof(book), 1, b_user2);
					}
					fclose(b_user1);
					fclose(b_user2);
				}

				if (fopen_s(&b_user1, a, "wb") || fopen_s(&b_user2, b, "rb"))
					perror("Error");
				else
				{
					book str1;
					while (!feof(b_user2))
					{
						fread(&str1, sizeof(book), 1, b_user2);
						if (feof(b_user2))
							break;
						if (str1.id != str.id)
							fwrite(&str1, sizeof(book), 1, b_user1);
					}
					fclose(b_user1);
					fclose(b_user2);
				}
				remove(b);
				return 1;
			}
		}
	}
	out_RED("Такой книги у вас нет");
	return 0;
}

void userfunc(user& client)
{
	book str;
	int f;
	bool b = 0, arr = 1;

	while (arr)
	{
		cout << endl << "1 - Взять книгу" << endl << "2 - Вернуть книгу" << endl
			<< "______________________" << endl << "Введите номер функции: ";
		char a[100];
		cin >> a;
		f = input1_2(a);

		cout << endl << "Введите название книги: ";
		cin >> str.name;
		cout << "Введите автора: ";
		cin >> str.writer;
		if (f == 1)
		{
			if (b_library(str))
			{
				if (str.number == 0)
					cout << "Такой книги нет в наличии" << endl;
				else
				{
					cout << "Книга: " << str.name << endl << "Автор: " << str.writer << endl << "ЕСТЬ в наличии." << endl << endl << "Хотите взять?" << endl;
					cout << "1 - ДА" << endl << "0 - НЕТ" << endl << "_______" << endl;
					cin >> b;

					if (b == 1)
					{
						str.number -= 1;
						book_edit(str, 3);
						user_book_add(client, str);
						out_GREEN("Книга успешно взята");
					}
				}
			}
			else
				out_BLUE_RED("Такой книги нет в библиотеке");

			cout << endl << "Хотите продолжить поиск?" << endl
				<< "1 - ДА" << endl << "0 - НЕТ" << endl << "_______" << endl;
			cin >> arr;
		}
		else if (f == 2)
		{
			if (b_library(str) && user_book_check(client, str))
			{
				str.number += 1;
				book_edit(str, 3);
				out_GREEN("Книга успешно возвращена");
			}
			else if (!b_library(str))
				out_BLUE_RED("Такой книги нет в библиотеке");
			arr = 0;
		}
	}
}

void adminfunc(user& client)
{
	int k;
	book str;
	//Регистрация книги состоит из ID книги, количества книг , название книги, автора
	cout << endl << "1 - Посмотреть информацию по книге" << endl << "2 - Регистрация новой книги" << endl << "3 - Удаление книги" << endl
		<< "4 - Редактирование информации и книге" << endl
		<< "______________________" << endl << "Введите номер функции: ";
	char a[100];
	cin >> a;
	k = input1_2_3_4(a);
	cout << endl;
	switch (k)
	{
	case 1:
		cout << "1 - По ID" << endl << "2 - По названию и автору" << endl;
		cout << endl << "______________________" << endl;
		cout << "Введите номер функции: ";
		char a[100];
		cin >> a;
		k = input1_2(a);
		if (k == 1)
		{
			cout << "Введите ID книги: ";
			cin >> str.id;
			book_search_id(str);
		}
		if (k == 2)
		{
			cout << endl << "Введите название книги: ";
			cin >> str.name;
			cout << "Введите автора: ";
			cin >> str.writer;
			book_search_nameandwriter(str);
		}
		break;
	case 2:
		book_registration();
		break;
	case 3:
		book_delete();
		break;
	case 4:
		int b;
		book b_ch;
		while (1)
		{
			cout << "Введите ID книги: ";
			cin >> b_ch.id;

			if (book_search_id(b_ch))
			{
				cout << "Что хотите отредактировать?" << endl << "1 - Название" << endl << "2 - Автора" << endl << "3 - Количество" << endl << "______________" << endl;;
				char a[100];
				cin >> a;
				b = input1_2_3(a);
				switch (b)
				{
				case 1:
					cout << endl << "Введите новое название: " << endl;
					cin >> b_ch.name;
					break;
				case 2:
					cout << endl << "Введите нового автора: " << endl;
					cin >> b_ch.writer;
					break;
				case 3:
					cout << endl << "Введите новое количество: " << endl;
					cin >> b_ch.number;
					break;
				default:
					out_RED("Номер функции введен не правильно!");
					break;
				}
				book_edit(b_ch, b);
				out_GREEN("Книга отредактирована");
				break;
			}
			else
				out_BLUE_RED("Такой книги нет в наличии!");
		}
		break;
	default:
		break;
	}
}

void verification(user& client)
{
	switch (client.role)
	{
	case 1: userfunc(client); break;
	case 2: adminfunc(client); break;
	default:
		break;
	}
}

void menu(user& client)
{
	bool bw = 1;
	int k;
	while (bw)
	{
		cout << "1 - авторизоваться" << endl << "2 - зарегистрироваться" << endl << "______________________" << endl;
		cout << "Введите номер функции: ";
		char a[100];
		cin >> a;
		k = input1_2(a);
		if (k != 1 && k != 2)
			k = 0;
			//out_RED("Номер функции введен не правильно!");
		else
		{
			if (k == 1)
			{
				int z = 0;
				while (z < 3)
				{
					char login[20], password[20];
					cout << "Введите логин: ";
					cin >> login;
					cout << "Введите пароль: ";
					cin >> password;
					logpass(login, password, client);

					if (b_keys(client) == 1)
					{
						bw = 0;
						break;
					}
					out_BLUE_RED("Проверьте правильность написания логина или пароля!");
					z++;
				}
				if (z == 3)
				{
					cout << "Зарегистрируйтесь в системе." << endl;
					k = 2;
				}
			}
			if (k == 2)
			{
				createPerson(client);
				break;
			}
		}
	}
	while (1)
	{
		verification(client);
		cout << endl << "Желаете продолжить работу с библиотекой?" << endl;
		cout << "1 - Да" << endl << "2 - Нет" << endl << "_______" << endl;
		char a[100];
		cin >> a;
		k = input1_2(a);
		if (k == 2)
		{
			out_GREEN("Спасибо, что воспользовались нашей библиотекой!");
			break;
		}
	}
}

int main()
{
	FILE* keys;
	fopen_s(&keys, "data1", "a+b");
	fclose(keys);
	fopen_s(&keys, "library", "a+b");
	fclose(keys);
	user client;
	setlocale(LC_ALL, "");
	//HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	menu(client);
}
