#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include "CipherMode.hpp"

#include <iostream>
#include <string>
#include <map>

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */

class PlayfairCipher
{
    public:
    /**
     * \brief Create a new PlayfairCipher with the given key
     *
     * \param key the key to use in the cipher
     */
       explicit PlayfairCipher(const std::string& key);
     /**
     * \brief Recalling the setkey function for use within the Playfair cipher
     *
     * \param key the string to convert into the key to be used in the cipher
     */
        void setKey(const std::string& key);
    /**
     * \brief Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
        std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;
    private:
    /**
     * \brief Create a new key_ function
     *
     * \param key_ the string to convert into the key to be used in the cipher
     */
        std::string key_;
    /**
     * \brief Storing the map co-ords and setKey function
     * 
     * \param charLookup_ Reference for the script to find the character in the map
     * \param coordLookup_ Reference for the script to find the co-ord location in the map
    */
   using PlayfairCoord = std::pair<std::size_t, std::size_t>;
   std::map<char, PlayfairCoord> charLookup_;
   std::map<PlayfairCoord, char> coordLookup_;
};

#endif