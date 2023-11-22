     #include "PlayfairCipher.hpp"

     #include <string>
     #include <iostream>
     #include <algorithm>
     #include <iterator>
     #include <map>
     #include <vector>
     
      PlayfairCipher::PlayfairCipher(const std::string& key)
      {
        this->setKey(key);
      }

        void PlayfairCipher::setKey(const std::string& key)
{
    //store the original key
    key_=key;

    //Append the alphabet
    key_.append("ABCDEFGHIJKLMNOPQRSTUVWXY");

    //Make sure the key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper);

    //Remove non-alpha character
    key_.erase(std::remove_if(key_.begin(), key_.end(), [](char c) {return !std::isalpha(c); }),
                key_.end());

    //Change I to J
    std::transform(key_.begin(), key_.end(), key_.begin(), [](char c) {return (c== 'J') ? 'I' : c;});

    //Remove duplicate letters
    std::string lettersfound{""};
    auto detectDuplicates = [&](char c)
    {
      if (lettersfound.find(c) == std::string::npos)
        {
          lettersfound += c;
          return false;
        }
        else
        {
          return true;
        }
    };

    key_.erase(
      std::remove_if(key_.begin(), key_.end(), detectDuplicates),
      key_.end());

    //Store the co-ords of each letter
    //Store the playfair cipher key map

    for (std::size_t i; i<25; ++i)
    {
      char c = key_[i];
      charLookup_[c] = std::make_pair(i/5,i%5);
      coordLookup_[std::make_pair(i/5,i%5)] = c;
    }
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode /*cipherMode*/) const
{
    //Change J to I
    std::string outputText{inputText};
    std::transform(outputText.begin(), outputText.end(), outputText.begin(), [](char c) {return (c== 'J') ? 'I' : c;});

    //If repeated chars in a digraph add an X or Q if XX
    std::string tmpText;
    for(std::size_t i{0}; i<outputText.size(); i+=2)
    {
      if (i+1>=outputText.size())
      {

        //If the size input is odd, add a trailing Z
        //if Z is there, change ZZ to Q//
        tmpText += outputText[i];
        tmpText += (outputText[i] == 'Z') ? 'Q' : 'Z';
        break;
      }

      if (outputText[i] == outputText[i+1])
      {
        tmpText += outputText[i];
        tmpText += (outputText[i] == 'X') ? 'Q' : 'X';
        --i;
      }
      else
      {
        tmpText += outputText[i];
        tmpText += outputText[i+1];
      }
    }

    outputText.swap(tmpText);

    //Loop over the inputs in the digraphs
    //i+=2 loop, no need to check beyond it, use output text i i+1 to give coords, replace output text with new chars//

    std::string::size_type i = 0;
    while (i+1 < outputText.size())
    {
      char firstChar = outputText[i];
      char secondChar = outputText[i+1];

      // - Find the co-ords in the grid for each digraph
      auto firstCoord = charLookup_.at(firstChar);
      auto secondCoord = charLookup_.at(secondChar);

      // - Apply the rules to these co-ords to get 'new' co-ords
      if (firstCoord.first == secondCoord.first)
      {
          firstCoord.second = (firstCoord.second + 1) %5;
          secondCoord.second = (secondCoord.second + 1) %5;
      }
        else if (firstCoord.second == secondCoord.second)
        {
          firstCoord.first = (firstCoord.first + 1) %5;
          secondCoord.first = (secondCoord.first + 1) %5;
        }

          else 
          {
          std::swap(firstCoord.second, secondCoord.second);
          }

    // -Find the letter associated with the new co-ords
      outputText[i] = coordLookup_.at(firstCoord);
      outputText[i+1] = coordLookup_.at(secondCoord);

      i+=2;
    }

    //Return the text
    return outputText;
}
