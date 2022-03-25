#ifndef LOG_H
#define LOG_H

class Log{
    private:
        //Error message
        std::string msg;
    public:
        //Log SDL error
        void SDL(const std::string& msg);
        //Log IMG error
        void IMG(const std::string& msg);
};
#endif