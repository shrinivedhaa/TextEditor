#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Line
{
    int linenumber;
    std::string details;
};

std::string fileName;
std::vector<Line> lines;
int pos = 0;
std::string phrase = "";

class pro
{
public:
    void create(std::string fileName)
    {
        //CREATE A NEW FILE
        std::ofstream file(fileName); //ofstream is used for writing into files.
        if (file.is_open())
        {
            std::cout << "File created successfully!" << std::endl;
            file.close();
        }
        else
        {
            std::cout << "Failed to create the file." << std::endl;
        }
    }

    void openfile(std::string fileName)
    {
        std::ifstream file(fileName); //ifstream is used to read from files.
        if (file.is_open())
        {
            //Open a file
            std::string line;
            lines.clear();
            int linenumber = 1;
            while (std::getline(file, line))
            {
                //load contents from the file into the vector
                lines.push_back({linenumber, line});
                linenumber++;
            }
            std::cout << "File '" << fileName << "' opened.\n";
            if (lines.empty())
            {
                std::cout << "Empty file.\n";
            }
            else
            {
                //loading the contents on to the terminal
                std::cout << "File contents:\n";
                for (auto i : lines)
                    std::cout << "[" << i.linenumber << "] " << i.details << std::endl;
            }
            //file.close();
        }
    }

    void save()
    {
        char ch;
        std::cout << "Where do you want to save your contents?\n1. New File\n2. Already Open File" << std::endl;
        std::cin >> ch;
        switch (ch)
        {
        case '1':
        {
            //save contents into a new file
            std::string new_file;
            std::cout << "Enter new file name" << std::endl;
            std::cin >> new_file;
            new_file += ".txt";
            std::ofstream file(new_file);
            if (file.is_open())
            {
                for (auto i : lines)
                    file << i.details << '\n';
                std::cout << "File saved." << std::endl;
            }
            else
                throw std::runtime_error("Error saving the file.");
            file.close();
            break;
        }

        case '2':
        {
            //save contents in the file that is currently open
            std::ofstream file(fileName);
            if (file.is_open())
            {
                for (auto i : lines)
                    file << i.details << '\n';
                std::cout << "File saved." << std::endl;
            }
            else
                throw std::runtime_error("Error saving the file.");
            file.close();
            break;
        }

        default:
            std::cout << "Wrong Choice! Enter 3 to save your contents" << std::endl;
            break;
        }
    }
    void ins_txt()
    {
        std::string textToInsert;
        std::cout<<"Enter the text to be entered: ";
        std::cin.ignore();
        std::getline(std::cin, textToInsert);
        if(lines.empty())
        {
            //if file is empty, write the contents in the first line.
            lines.push_back({1,textToInsert});
        }
        else
        {
            char ins_ch;
            std::cout << "Enter:\n1. Insert text at current cursor position\n2. Insert text at the end of the file" << std::endl;
            std::cin >> ins_ch;
            switch (ins_ch)
            {
                case '1':
                {
                    if(pos!=0)
                    {
                        // Code for inserting text at the current cursor position in case of single line file
                        size_t position = lines[pos - 1].details.find(phrase);
                        std::string part1 = lines[pos - 1].details.substr(0, position + phrase.length());
                        std::string part2 = textToInsert;
                        std::string part3 = lines[pos - 1].details.substr(position + phrase.length());
                        std::string parts = part1 + part2 + part3;
                        lines[pos - 1].details = parts;
                    }
                    else
                    {
                        // Code for inserting text at the current cursor position otherwise
                        size_t position = lines[pos].details.find(phrase);
                        std::string part1 = lines[pos].details.substr(0, position + phrase.length());
                        std::string part2 = textToInsert;
                        std::string part3 = lines[pos].details.substr(position + phrase.length());
                        std::string parts = part1 + part2 + part3;
                        lines[pos].details = parts;
                    }
                    break;
                }
                case '2':
                {
                    // Code for inserting text at the end of the file
                    int temp = lines.size() + 1;
                    lines.push_back({ temp, textToInsert });
                    break;
                }
                default:
                    std::cout << "Invalid choice!" << std::endl;
                    break;
            }
        }
    }

    void del_txt()
    {
        disp();
        std::string phr;
        std::cout<<"Enter line number:"<<std::endl;
        std::cin>>pos;
        std::cout << lines[pos-1].details << std::endl;
        std::cout<<"Enter the phrase:"<<std::endl;
        std::cin>>phr;
        if (pos >= 1 && pos <= lines.size())
        {
            std::size_t position = lines[pos-1].details.find(phr);
            if (position != std::string::npos)
                lines[pos-1].details.erase(position, phr.length());
        }
    }

    void mov_cursor()
    {
        disp();
        std::cout<<"Enter line number:"<<std::endl;
        std::cin>>pos;
        std::cout << lines[pos-1].details << std::endl;
        std::cout<<"Enter the phrase:"<<std::endl;
        std::cin>>phrase;
        std::cout<<"Cursor moved!"<<std::endl;
    }

    void disp()
    {
        std::cout << "File contents:\n";
        for (auto i : lines)
            std::cout << "[" << i.linenumber << "] " << i.details << std::endl;
    }
    
    void search()
    {
        std::string squery;
        std::cout << "Enter search query:" << std::endl;
        std::cin >> squery;
        int count=0;
        for(auto& i:lines)
        {
            size_t first=0;
            while((first=i.details.find(squery,first))!=std::string::npos)
            {
                first+=squery.size();
                count++;
            }
        }
        if(count>0)
            std::cout << squery << " occurred " << count << " time(s)  " << std::endl;
        else
            std::cout << squery << " was not found in the file" << std::endl;
    }
    
    void replace()
    {
        std::string query, rep;
        std::cout << "Enter the search query" << std::endl;
        std::cin >> query;
        std::cout << "Enter the text to be replaced with" << std::endl;
        std::cin >> rep;
        int count = 0;
        for (auto &i : lines)
        {
            size_t first = 0;
            // npos: a constant static member value with the highest possible value for an element of type size_t. (until the end of the string)
            while ((first = i.details.find(query, first)) != std::string::npos)
            {
                i.details.replace(first, query.size(), rep);
                first += rep.size();
                count++;
            }
        }
        if (count > 0)
            std::cout << query << " occurred " << count << " time(s) and has been replaced with " << rep << std::endl;
        else
            std::cout << query << " was not found in the file" << std::endl;
    }
};

int main()
{
    char choice;
    pro ob1;
    do
    {
        std::cout << "Enter:\n1.Create a file\n2.Open an existing file\n3.Save the current file\n4.Edit the current file\n5.Search the current file\n6.Replace text within the current file\n7.Exit the program\n"<< std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case '1':
            std::cout << "YOU ARE CREATING A FILE!\n" << std::endl;
            std::cout << "Enter the file name:\n";
            std::cin >> fileName;
            ob1.create(fileName);
            break;
        case '2':
            std::cout << "YOU ARE OPENING A FILE!\n" << std::endl;
            std::cout << "Enter the file name:\n";
            std::cin >> fileName;
            ob1.openfile(fileName);
            break;
        case '3':
            std::cout << "YOU ARE SAVING A FILE!\n" << std::endl;
            ob1.save();
            break;
        case '4':
            std::cout << "YOU ARE EDITING!\n" << std::endl;
            char edit_ch;
            std::cout << "Enter:\na. Insert Text\nb. Delete Text\nc. Move Cursor\nd. Display The Current File " << std::endl;
            std::cin >> edit_ch;
            edit_ch = (char)tolower(edit_ch);
            switch(edit_ch)
            {
            case 'a':
                std::cout << "YOU ARE INSERTING TEXT!\n" << std::endl;
                ob1.ins_txt();
                break;
            case 'b':
                std::cout << "YOU ARE DELETING A TEXT!\n" << std::endl;
                ob1.del_txt();
                break;
            case 'c':
                std::cout << "YOU ARE MOVING THE CURSOR!\n" << std::endl;
                ob1.mov_cursor();
                break;
            case 'd':
                std::cout << "YOU ARE VIEWING THE FILE!\n" << std::endl;
                ob1.disp();
                break;
            default:
                std::cout << "WRONG CHOICE" << std::endl;
            }
            break;
        case '5':
            std::cout << "YOU ARE SEARCHING IN THIS FILE!\n" << std::endl;
            ob1.search();
            break;
        case '6':
            std::cout << "YOU ARE REPLACING TEXT IN THIS FILE!\n" << std::endl;
            ob1.replace();
            break;
        case '7':
            std::cout << "YOU ARE EXITING!! BYE!!\n" << std::endl;
            exit(1);
            break;
        default:
            std::cout << "ENTER A VALID CHOICE!!\n" << std::endl;
        }
    } while (choice);
    return 0;
}
