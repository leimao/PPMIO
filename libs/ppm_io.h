#include <string>

class PPM
{
public:
    // Constructors
    // Default constructor
    PPM() = default;
    // Create PPM instance from image file
    PPM(const std::string & filepath);
    // Create PPM instance from data
    PPM(const uint8_t * buffer, const int h, const int w, const int max, const std::string magic);
    // Copy constructor
    // Create PPM instance from another PPM instance
    PPM(const PPM & ppm);
    // Destructors
    ~PPM();
    // Assign operator
    // Assign one PPM instance to another
    PPM & operator = (const PPM & ppm);
    // Equal operator
    // Check if two PPM instances are equivalent
    bool operator == (const PPM & ppm) const;
    // Read PPM from file
    int read(const std::string & filepath);
    // Save PPM to file
    int write(const std::string & filepath) const;
    // Load array as PPM
    void load(const uint8_t * buffer, const int h, const int w, const int max, const std::string magic);
    // Get attributes
    std::string getMagic() const;
    std::string getFilepath() const;
    int getH() const;
    int getW() const;
    int getMax() const;
    uint8_t * getImageHandler() const;
    // Set magic to P3 (false) or P6 (true)
    void setBinary(const bool isBinary);
private:
    std::string mMagic, mFilepath;
    int mH, mW, mMax;
    uint8_t * mBuffer = nullptr;
};

