#include "Client.h"

using namespace std;

Client::Client():
    CM()
{
    this -> board = "";
    this -> thread_no = 0;
    this -> page = 0;
}

Json::Value
Client::getContent()
{
    string path;
    ifstream content_stream;
    Json::Value content;
    path = this -> CM.getContentPath(this -> board, this -> thread_no);
    content_stream.open(path.c_str(), std::ios::binary);
    if(content_stream.bad())
        cout << "Somethings wrong" << endl;
    content_stream >> content;
    content_stream.close();
    return content;
}

void
Client::enterThread(unsigned int thread)
{
    Json::Value thread_info;
    unsigned char page = this -> page;
    thread_info = getContent();
    this -> thread_no = 
        thread_info[(int)page]["threads"][(int)thread]["no"].asInt();
}

bool
is_number(const string& num)
{
    std::string::const_iterator it = num.begin();
    while (it != num.end() && std::isdigit(*it)) ++it;
    return !num.empty() && it == num.end();
}

bool
Client::parse_command(const char* line, PrintStream &out)
{
    fstream content_file;
    stringstream command;
    string args[3], file_path;
    Json::Value content;
    Reply *replies;
    int count, threads;
    size_t reply_count;
    count = 0;
    command.str(line);
    while(std::getline(command,args[count++],' ')){}

    if(args[0] == "cd")
    {
        if (args[1] == "-p")
        {
            this -> thread_no = 0;
            this -> page = (unsigned char) std::atoi(args[2].c_str());
        } 
        else if (args[1] == "..")
        {
            if(this -> thread_no == 0 && this -> page > 0)
                this -> page--;
            else
                this -> thread_no = 0;
        }
        else if(is_number(args[1]))
        {
            enterThread(std::atoi(args[1].c_str()));
            CM.prepCache(this -> board, this -> thread_no);
        }
        else
        {
            this -> board = args[1];
            this -> thread_no = 0;
            CM.prepCache(this -> board,this -> thread_no);
        }
    }
    else if (args[0] == "show" || args[0] == "ls")
    {
        if(this -> board.empty())
        {
            out <<  RED_FG << "Theres nothing here!" << RESET << endl;
            return true;
        }
        if(this -> thread_no == 0)
        {
            content = getContent();
            threads = content[(int)this -> page]["threads"].size();
            out << RED_FG 
                << "/" + this -> board + "/\t"
                << "Page: " 
                << YELLOW_FG 
                << (int)this -> page 
                << RESET
                << endl;
            for(count = 0; count < threads; count++)
            {
                out << RED_FG
                    << count
                    << ": "
                    << YELLOW_FG
                    << content[this -> page]["threads"][count]["no"]
                    << RED_FG
                    << " ("
                    << content[this -> page]["threads"][count]["replies"]
                    << " replies)"
                    << RESET
                    << endl;
            }
        }
        else
        {
            content = getContent();
            Thread thread(content);
            out << thread.getOP();
            out.indent(5);
            replies = thread.getReplies(reply_count);
            for(count = 0; count < reply_count; count++)
                out << replies[count];
            out.indent(0);
            
        }
    }
    else if (args[0] == "refresh")
    {
        CM.setState(FORCE_REFRESH);
        CM.prepCache(this -> board, this -> thread_no);
        CM.setState(REFRESH);
    }
    else
        return false;
    return true;
}

