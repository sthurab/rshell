#ifndef PARSER_H
#define PARSER_H

class parser {
    private:
        string input;
        vector<char*> commands;
    public:
        parser();
        parser(string str);
        void interpret();
};

#endif