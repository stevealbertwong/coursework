

  char charArray[]={'h','e','l','l','o',' ','w','o','r','l','d','\0'};
  char *i = &charArray[0];
  char *j = charArray;
  cout << j;

  const char *char_ptr = "hellow world";
  char* erase_const = const_cast<char*>(char_ptr);
  cout << erase_const;