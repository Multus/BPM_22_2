// Example program
#include <iostream>
#include <string>
#include <array>

int main()
{
  int t = 0;
  int n = 0;
  int k = 0;
  int skip_len = 0;
  std::string s = "";
  std::cin >> t;
  unsigned char current_char = ' ';
  for(int i = 0; i < t; i += 1)
  {
  		// std::cout << "New input" << std::endl;
  
      std::array<int, 256> is_char_used = {0};
	  
      std::cin >> n;
      std::cin >> s;
      s += '0';
      std::cin >> k;
      for(int j = 0; j < k; j += 1)
      {
          std::cin >> current_char;
          is_char_used[current_char] = 1;
		     // std::cout << int(current_char) << " ";
      }
      int count = -1; //т.к. прогон, взывающий тревогу тоже считается
      for(bool alarm = false; !alarm; count += 1)
      {
        alarm = true;
			// std::cout << count << std::endl;
			// std::cout << s.length() << std::endl;
        for(int j = 0; j < s.length(); j += 1)
        {
					skip_len = 1;
					for(; s[j + skip_len] == '0'; skip_len += 1){}
		
            if(is_char_used[s[j + skip_len]] && s[j] != '0')
            {
                alarm = false;
                s[j] = '0';
            }
        }
      }
      std::cout << count << std::endl;
  }
}
