#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <cstring>

#include "ppm_io.h"

int PPM::read(const std::string & filepath)
{
    std::ifstream infile(filepath, std::ifstream::binary);
    // Examine if the file could be opened successfully
    if (!infile.is_open()) 
    {
        std::cout << "Failed to open " << filepath << std::endl;
        return 1;
    }

    infile >> mMagic;
    infile.seekg(1, infile.cur);
    char c;
    infile.get(c);
    if (c == '#')
    {
        // We got comments in the PPM image and skip the comments
        while (c != '\n')
        {
            infile.get(c);
        }
    }
    else
    {
        infile.seekg(-1, infile.cur);
    }
    
    infile >> mW >> mH >> mMax;
    if (mMax != 255)
    {
        std::cout << "Failed to read " << filepath << std::endl;
        std::cout << "Got PPM maximum value: " << mMax << std::endl;
        std::cout << "Maximum pixel has to be 255" << std::endl;
        return 1;
    }

    mBuffer = new uint8_t[mW * mH * 3];

    // ASCII
    if (mMagic == "P3")
    {
        for (int i = 0; i < mW * mH * 3; i ++)
        {
            std::string pixel_str;
            infile >> pixel_str;
            mBuffer[i] = static_cast<uint8_t> (std::stoi(pixel_str));
        }
    }
    // Binary
    else if (mMagic == "P6")
    {
        // Move curser once to skip '\n'
        infile.seekg(1, infile.cur);
        infile.read(reinterpret_cast<char *>(mBuffer), mW * mH * 3);
    }
    else
    {
        std::cout << "Unrecognized PPM format" << std::endl;
        std::cout << "Got PPM magic number: " << mMagic << std::endl;
        std::cout << "PPM magic number should be either P3 or P6" << std::endl;
        return 1;
    }

    mFilepath = filepath;
    
    return 0;
}


int PPM::write(const std::string & filepath) const
{
    std::ofstream outfile(filepath, std::ofstream::binary);
    if (outfile.fail())
    {
        std::cout << "Failed to write " << filepath << std::endl;
        return 1;
    }
    outfile << mMagic << "\n" << mW << " " << mH << "\n" << mMax << "\n";

    if (mMagic == "P3")
    {
        for (int i = 0; i < mH; i ++)
        {
            for (int j = 0; j < mW * 3; j ++)
            {
                outfile << std::to_string(static_cast<uint8_t>(mBuffer[i * mW * 3 + j])) << " ";
            }
            outfile << "\n";
        }
    }
    else if (mMagic == "P6")
    {
        outfile.write(reinterpret_cast<char *>(mBuffer), mW * mH * 3);
    }
    else
    {
        std::cout << "Unrecognized PPM format" << std::endl;
        std::cout << "Got PPM magic number: " << mMagic << std::endl;
        std::cout << "PPM magic number should be either P3 or P6" << std::endl;
        return 1;
    }

    return 0;
}

void PPM::load(const uint8_t * buffer, const int h, const int w, const int max, const std::string magic)
{
    mH = h;
    mW = w;
    mMax = max;
    mMagic = magic;
    if (mBuffer != nullptr)
    {
        delete [] mBuffer;
        mBuffer = nullptr;
    }
    mBuffer = new uint8_t[w * h * 3];
    std::memcpy(mBuffer, buffer, w * h * 3 * sizeof(uint8_t));
}

void PPM::setBinary(const bool isBinary)
{
    if (isBinary == false)
    {
        mMagic = "P3";
    }
    else
    {
        mMagic = "P6";
    }
}


PPM::PPM(const std::string & filepath)
{
    read(filepath);
}

PPM::PPM(const uint8_t * buffer, const int h, const int w, const int max, const std::string magic)
{
    load(buffer, h, w, max, magic);
}


PPM::PPM(const PPM & ppm)
{
    std::string magic = ppm.getMagic();
    std::string filepath = ppm.getFilepath();
    int h = ppm.getH();
    int w = ppm.getW();
    int max = ppm.getMax();
    uint8_t * buffer = ppm.getImageHandler();
    load(buffer, h, w, max, magic);
}




PPM & PPM::operator = (const PPM & ppm)
{
    if (mBuffer != nullptr)
    {
        delete [] mBuffer;
        mBuffer = nullptr;
    }
    std::string magic = ppm.getMagic();
    std::string filepath = ppm.getFilepath();
    int h = ppm.getH();
    int w = ppm.getW();
    int max = ppm.getMax();
    uint8_t * buffer = ppm.getImageHandler();
    load(buffer, h, w, max, magic);
    return *this;
}

bool PPM::operator == (const PPM & ppm) const
{
    if ((mH == ppm.getH()) && (mW == ppm.getW()) && (mMax == ppm.getMax()))
    {
        for (int i = 0; i < mH * mW * 3; i ++)
        {
            uint8_t * buffer = ppm.getImageHandler();
            if (mBuffer[i] != buffer[i])
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
    
}

PPM::~PPM()
{
    if (mBuffer != nullptr)
    {
        delete [] mBuffer;
    }
}

std::string PPM::getMagic() const
{
    return mMagic;
}

std::string PPM::getFilepath() const
{
    return mFilepath;
}

int PPM::getH() const
{
    return mH;
}

int PPM::getW() const
{
    return mW;
}

int PPM::getMax() const
{
    return mMax;
}

uint8_t * PPM::getImageHandler() const
{
    return mBuffer;
}
