#include <Visitor.h>
#include <string>
#include <vector>

class SyntaxTreePrinter : public Visitor {
public:
    virtual void visit( const NumExpression* );
    virtual void visit( const BinopExpression* );

    std::string ToString() const;

private:
    static int globalIndex;
    std::string top;
    std::vector<std::string> content;
};