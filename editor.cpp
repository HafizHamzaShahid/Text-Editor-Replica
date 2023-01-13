#include <fstream>
#include <iostream>
#include <stdlib.h>

# include "myconsole.h"
# include "editor.h"
#include "LinkList.h"
using namespace std;


//-------------------------------Color Codes------------------------------//
// Color Codes Hexadecimal values for both Fore Ground and Back Ground //ForeGround|BackGround
int B_BLACK = 0x00;	int B_Royal_Blue = 0x10;	int B_Dark_Green = 0x20;
int B_Tale_Blue = 0x30;	int B_Dark_Red = 0x40;	int B_Purple = 0x50;
int B_Tale_Green = 0x60;	int B_Light_Grey = 0x70; int B_Dark_Gray = 0x80;
int B_Light_Blue = 0x90; int B_Light_Green = 0xA0;	int B_Sky_Blue = 0xB0;
int B_Red = 0xC0;	int B_Pink = 0xD0;	int B_Yellow = 0xE0;
int B_White = 0xF0;

int F_BLACK = 0x00;	int F_Royal_Blue = 0x01; int F_Dark_Green = 0x02;
int F_Tale_Blue = 0x03;	int F_Dark_Red = 0x04;	int F_Purple = 0x05;
int F_Tale_Green = 0x06;	int F_Light_Grey = 0x07; int F_Dark_Gray = 0x08;
int F_Light_Blue = 0x09; int F_Light_Green = 0x0A;	int F_Sky_Blue = 0x0B;
int F_Red = 0x0C;	int F_Pink = 0x0D;	int F_Yellow = 0x0E;
int F_White = 0x0F;

//-------------------------------POINT CLASS------------------------------//
//initialize MaxPoint
point point::MaxPoint(MAX_X, MAX_Y);
bool point::incrementX()
{
	bool returnValue = true;
	if (x < MaxPoint.x)
		x++;
	else if (y < MaxPoint.y)
	{
		x = 0;
		y = y + 1;
	}
	else
		returnValue = false;

	return returnValue;
}
bool point::incrementY()
{
	bool returnValue = true;
	if (y < MaxPoint.y)
		y++;
	else
		returnValue = false;

	return returnValue;

}
bool point::decrementX()
{
	bool returnValue = true;
	if (x > 0)
		x--;
	else if (y > 0)
	{
		y--;
		x = MaxPoint.x;
	}
	else
		returnValue = false;

	return returnValue;
}
bool point::decrementY()
{
	bool returnValue = true;
	if (y > 0)
		y--;
	else
		returnValue = false;

	return returnValue;

}

//-------------------------------END OF POINT CLASS------------------------------------------------//

//--------------------------The function Where you will write code--------------------------------//
int mainEditor()
{
	int key = 0;
	bool stop = false;
	point currentPosition(0, 0);
	currentPosition.setMaxPoint(MAX_X, MAX_Y);
	bool specialKey = false;
	DoublyLinkedList<char> LinkList;
	LinkList.Insertat_at_Head(key);
	DoublyLinkedList<char>::Iterator itr = LinkList.Begin();
	itr--;
	while (!stop)
	{
		key = CheckWhichKeyPressed(specialKey);
		//escape key
		if (key == ESCKEY)
			stop = true;
		//printable character...only adds to the end of text
		//this will not do insertions in between text
		//add code here to insert characters within text
		else if (!specialKey && key >= 32 && key <= 126)
		{
			//1
			if (currentPosition.getX() < MAX_X)
			{
				LinkList.Insert(itr, (char)key);
				itr++;
				cout << (char)key;
				currentPosition.incrementX();
				//You can change color of text by calling this function
				//SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK | B_Sky_Blue);   //ForeGround|BackGround
				//currentPosition.incrementX();
				ClearScreen();

				point p(0, 0);
				PlaceCursor(0, 0);
				for (DoublyLinkedList<char>::Iterator t = LinkList.Begin(); t != LinkList.End(); t++)
				{
					if (t.current->data != '\n')
					{
						cout << *t;
						SetColorAtPoint(p.getX(), p.getY(), F_BLACK | B_Sky_Blue);

						p.incrementX();
					}
					else
					{
						cout << *t;
						p.setX(0);
						p.incrementY();
					}
				}
			}
			else if (currentPosition.getY() < MAX_Y)
			{
				currentPosition.incrementY();
				currentPosition.setX(0);
			}
		}
		else if (specialKey && key == LEFTKEY)
		{
			if (itr != LinkList.Begin())
			{
				if (itr.current->data != '\n')
				{
					--itr;
					currentPosition.decrementX();
				}
				else
				{
					currentPosition.decrementY();
					--itr;
				}
			}

		}
		else if (specialKey && key == RIGHTKEY)
		{
			if (itr.current->next != nullptr)
			{


				if (itr.current->data != '\n')
				{
					itr++;
					currentPosition.incrementX();
				}
				else
				{
					currentPosition.incrementY();
					currentPosition.setX(0);
					itr++;
				}
			}
		}
		else if (specialKey && key == UPKEY)
		{
			if (itr.current->prev != nullptr)
			{
				
				for (int i = 0; i < 100; i++)
				{
					currentPosition.decrementX();
					itr--;
				}
			}

			currentPosition.decrementY();
		}
		else if (specialKey && key == DOWNKEY)
		{
			//Update it so that cursur not move downword if it is at last line of text.
			if (itr.current->next != nullptr)
			{
				
				for (int i = 0; i < 100; i++)
				{
					currentPosition.incrementX();
					itr++;
				}
			}
			currentPosition.incrementY();
		}
		else if (key == ENTERKEY)
		{
			LinkList.Insert(itr, '\n');
			itr++;
			cout << ('\n');
			currentPosition.setX(0);
			currentPosition.incrementY();
		}
		else if (key == DELKEY)
		{
			//2
			cout << '\0';
			//call a function to handle 
			LinkList.Delete(itr);
			
			ClearScreen();

			point p(0, 0);
			PlaceCursor(0, 0);
			for (DoublyLinkedList<char>::Iterator t = LinkList.Begin(); t != LinkList.End(); t++)
			{
				if (t.current->data != '\n')
				{
					cout << *t;
					SetColorAtPoint(p.getX(), p.getY(), F_BLACK | B_Sky_Blue);

					p.incrementX();
				}
				else
				{
					cout << *t;
					p.setX(0);
					p.incrementY();
				}

				if (!p.decrementX() && p.getY() > 0) {
					cout << '\0';
					p.decrementY();
					p.setX(MAX_X);
				}
			}
		}
		else if (key == BACKSPACE)
		{
			cout << '\0';
			//3
			//handle backspace here
			LinkList.BackSpace(itr);
			itr--;
			ClearScreen();
			currentPosition.set(0, 0);
			PlaceCursor(0, 0);
			for (DoublyLinkedList<char>::Iterator t = LinkList.Begin(); t != LinkList.End(); t++)
			{
				if (t.current->data != '\n')
				{
					cout << *t;
					SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK | B_Sky_Blue);

					currentPosition.incrementX();
				}
				else
				{
					cout << *t;
					currentPosition.setX(0);
					currentPosition.incrementY();
				}
			}
			if (!currentPosition.decrementX() && currentPosition.getY() > 0) {
				cout << '\0';
				currentPosition.decrementY();
				currentPosition.setX(MAX_X);
			}
		}
		else if (key == F6KEY)
		{
		    //for clearing the screen
		    ClearScreen();
        }
		else if (key == F1KEY || key == F2KEY || key == F3KEY)
		{
			//handle search here
			//you can take the cursor at the bottom of the screen and get some input
			//for searching
			PlaceCursor(0, MAX_Y - 2);
			for (int i = 0; i < MAX_X; i++)
			{
				cout << '\0';
				currentPosition.incrementX();
			}
			cout << "Enter Search Text: " << endl;
			currentPosition.setX(strlen("Enter Search Text : "));
			currentPosition.setY(MAX_Y - 2);
			PlaceCursor(strlen("Enter Search Text : "), MAX_Y - 2);
			if (key == F1KEY)
			{
				//4
				DoublyLinkedList<char>::Iterator temp;
				bool val = false;
				while (!false)
				{
					key = CheckWhichKeyPressed(specialKey);
					//escape key
					if (key == ESCKEY)
						val = true;
					//printable character...only adds to the end of text
					//this will not do insertions in between text
					//add code here to insert characters within text
					else if (!specialKey && key >= 32 && key <= 126)
					{
						cout << (char)key;
						temp = LinkList.SearchFirst(key);
						currentPosition.set(0, 0);
						for (DoublyLinkedList<char>::Iterator t = LinkList.Begin(); t != LinkList.End(); t++)
						{
							if (t.current->data != '\n')
							{
								if (temp == t)
								{
									SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK | B_Yellow);
								}
								currentPosition.incrementX();
							}
							else
							{
								currentPosition.setX(0);
								currentPosition.incrementY();
							}
						}
					}
				}
				//Search for one instance of string and move cursor there
			}
			else if (key == F2KEY)
			{

				DoublyLinkedList<char>::Iterator* temp;
				bool val = false;
				while (!false)
				{
					key = CheckWhichKeyPressed(specialKey);
					//escape key
					if (key == ESCKEY)
						val = true;
					//printable character...only adds to the end of text
					//this will not do insertions in between text
					//add code here to insert characters within text
					else if (!specialKey && key >= 32 && key <= 126)
					{
						int i = 0;
						cout << (char)key;
						temp = LinkList.SearchAll(key);

						point tmp1(0, 0);
						for (DoublyLinkedList<char>::Iterator t = LinkList.Begin(); t != LinkList.End(); t++)
						{
							if (t.current->data != '\n')
							{
								if (temp[i] == t.current)
								{
									i++;
									SetColorAtPoint(tmp1.getX(), tmp1.getY(), F_BLACK | B_Yellow);

								}
								tmp1.incrementX();
							}
							else
							{
								tmp1.setX(0);
								tmp1.incrementY();
							}
						}
					}
				}
			}
			else
			{
				  //Search for all instances of string 
				  //Take a second input string 
				  //and replace all instances of first string with second string
				DoublyLinkedList<char> ::Iterator* it;
				point h(currentPosition.getX(), currentPosition.getY());
				PlaceCursor(50, MAX_Y - 2);
				cout << "Enter Replace Text: " << endl;
				currentPosition.setX(50 + strlen("Enter Replace Text : "));
				point t(50 + strlen("Enter Replace Text : "), MAX_Y - 2);
				currentPosition.setY(MAX_Y - 2);
				PlaceCursor(h.getX(), MAX_Y - 2);
				char* arr1 = new char[20];
				char* arr2 = new char[20];
				int i = 0, j = 0;
				bool stopp = false;
				while (!stopp)
				{
					key = CheckWhichKeyPressed(specialKey);


					if (!specialKey && key >= 32 && key <= 126)
					{
						arr1[i] = key;
						cout << (char)key;
						i += 1;
						currentPosition.incrementX();

					}
					else if (specialKey && key == RIGHTKEY)
					{
						arr1[i + 1] = '\0';
						PlaceCursor(t.getX(), t.getY());
						currentPosition.set(t.getX(), t.getY());
						while (key != ENTERKEY)
						{
							key = CheckWhichKeyPressed(specialKey);
							if (key >= 32 && key <= 126)
							{
								cout << (char)key;
								arr2[j] = key;
								j += 1;
								currentPosition.incrementX();

							}
						}
						arr2[j + 1] = '\0';

					}
					else if (key == ENTERKEY)
					{
						int s = 0;
						int* t = nullptr;
						LinkList.Search_And_Replace(arr1, arr2, s, t);

						int s1 = 0, s2 = 0;
						for (; arr1[s1] != '\0'; s1++)
						{
						}
						for (; arr2[s2] != '\0'; s2++)
						{
						}
						s1 -= 1;
						s2 -= 1;

						if (s1 < s2)
						{
							int l = 0;
							while (l < s)
							{
								l++;
							}

						}
						else if (s2 < s1)
						{
							int l = 0;
							while (l < s)
							{
								l++;
							}
						}
						while (s != 0)
						{
							stopp = true;
							if (s1 < s2)
							{
								int y = 0;
								while ((s2 - s1) != y)
								{
									currentPosition.incrementX();
									y++;
								}
							}
							if (s1 > s2)
							{
								int z = 0;
								while ((s1 - s2) != z)
								{
									currentPosition.decrementX();
									z++;
								}
							}
							s--;
						}
						ClearScreen();
						PlaceCursor(0, 0);
						point temp1(0, 0);
						itr = LinkList.Begin();
						if (LinkList.getHead()->next != nullptr)
						{
							for (DoublyLinkedList<char> ::Iterator pos = LinkList.Begin(); pos != LinkList.End(); pos++)
							{
								char k = *pos;
								if (k == '\n')
								{

									cout << ('\n');
									if (itr.current->next->next != nullptr)
										itr++;
									SetColorAtPoint(temp1.getX(), temp1.getY(), F_BLACK | B_Sky_Blue);
									temp1.incrementY();
									temp1.setX(0);
								}
								else
								{

									if (temp1.getX() < MAX_X)
									{
										cout << k;
										if (itr.current->next->next != nullptr)
											itr++;

										//You can change color of text by calling this function
										SetColorAtPoint(temp1.getX(), temp1.getY(), F_BLACK | B_Sky_Blue);   //ForeGround|BackGround
										temp1.incrementX();

									}
									else if (temp1.getY() < MAX_Y)
									{
										cout << ('\n');
										if (itr.current->next->next != nullptr)
											itr++;
										SetColorAtPoint(temp1.getX(), temp1.getY(), F_BLACK | B_Sky_Blue);
										temp1.incrementY();
										temp1.setX(0);
									}
								}

							}
						}

						PlaceCursor(temp1.getX(), temp1.getY());
						//temp.set(temp1.getX(), temp1.getY());
						currentPosition.set(temp1.getX() - 1, temp1.getY());
						break;
					}

					else if (key == ESCKEY)
					{
						stopp = true;
						ClearScreen();
						PlaceCursor(0, 0);
						point temp1(0, 0);
						for (DoublyLinkedList<char> ::Iterator pos = LinkList.Begin(); pos != LinkList.End(); pos++)
						{
							char k = *pos;
							if (k == '\n')
							{

								cout << ('\n');

								SetColorAtPoint(temp1.getX(), temp1.getY(), F_BLACK | B_Sky_Blue);
								temp1.incrementY();
								temp1.setX(0);
							}
							else
							{

								if (currentPosition.getX() < MAX_X)
								{
									cout << *pos;


									//You can change color of text by calling this function
									SetColorAtPoint(temp1.getX(), temp1.getY(), F_BLACK | B_Sky_Blue);   //ForeGround|BackGround
									temp1.incrementX();

								}
								else if (currentPosition.getY() < MAX_Y)
								{
									cout << ('\n');

									SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK | B_Sky_Blue);
									temp1.incrementY();
									temp1.setX(0);
								}
							}

						}
						PlaceCursor(currentPosition.getX(), currentPosition.getY());
						currentPosition.set(currentPosition.getX(), currentPosition.getY());
						break;
					}

				}

			}
		}
		
		else if (key == F4KEY)
		{
			//7
			ofstream fout("LinkFile.txt");
			for (DoublyLinkedList<char> ::Iterator iter = LinkList.Begin(); iter != LinkList.End(); iter++)
			{
				fout << *iter;
			}
			fout.close();
			//save to file
		}
		PlaceCursor(currentPosition.getX(), currentPosition.getY());

	}

	return 0;
}

//-------------------------------------------End Main Editor--------------------------//
int main()
{
	mainEditor();
	//cout << __cplusplus << endl;
	return 0;
}



