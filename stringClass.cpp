#include <iostream>
#include<cstring>
#include<vector>
#include<algorithm>

class String{
private:
    char* data;
    size_t length;
public:
    String(){data = new char[0]; length = 0;}

    String(const char* str){
        if(str != nullptr){
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        }
    }

    String(String const& str){
        if(str.data != nullptr)
        {
            length = str.length;
            data = new char[length + 1];
            strcpy(data, str.data);
        }
    }

    ~String(){delete[] data;}

    String& operator=(String const& str){
        if(this != &str){
            delete[] data;
            length = str.length;
            data = new char[length + 1];
            strcpy(data, str.data);
            return *this;
        }
        }

    String& operator=(const char* str){
        if(str != nullptr){
            delete[] data;
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
            return *this;
        }
    }
    
    String& operator=(String&& str){
        if (this != &str) {
            delete[] data;
            data = str.data;
            length = str.length;
            str.data = nullptr;
            str.length = 0;
        }
        return *this;
    }

    String& operator+=(String const& str){
        char* newData = new char[length + str.length + 1];
        strcpy(newData, data);
        strcpy(newData + length, str.data);
        delete[] data;
        data = newData;
        length += str.length;
        return *this;
    }

    String& operator+=(const char* str){
        if(str != nullptr)
        {
            char* newData = new char[length + strlen(str) + 1];
            strcpy(newData, data);
            strcpy(newData + length, str);
            delete[] data;
            data = newData;
            length += strlen(str);
        }
        else {std::cout << "Warning: Can't conatinate with nullptr\n";}
        return *this;
    }

    char* get_c_str() const{return data;}

    size_t len() const{return length;}
};

String operator+(String const& first, String const& second){
    String res(first);
    res += second;
    return res;
}

String operator+(String const& first, const char* second){
    String res(first);
    res += second;
    return res;
}

String operator+(const char* first, String const& second){
    String res(first);
    res += second;
    return res;
}

bool compareCaseInsens(String const& first, String const& second){
    size_t minSize = std::min(first.len(), second.len());
    for(size_t i = 0; i < minSize; ++i)
        if(tolower(first.get_c_str()[i]) < tolower(second.get_c_str()[i]))
            return true;
        else if(tolower(first.get_c_str()[i]) > tolower(second.get_c_str()[i]))
            return false;
    return first.len() < second.len();
}



int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout << "Warning: Missing arguments..." << std::endl;
        return 1;
    }
    std::vector<String> args;
    for(int i = 1; i < argc; ++i)
        args.push_back(String(argv[i]));
    std::sort(args.begin(), args.end(), compareCaseInsens);
    std::reverse(args.begin(), args.end());
    std::cout << "Sorted order:\n";
    for(auto str : args)
        std::cout << str.get_c_str() << std::endl;
    return 0;
}