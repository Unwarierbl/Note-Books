#include <SpreadsheetCell.h>

#include <optional>
#include <string>
#include <string_view>

class StringSpreadsheetCell : public SpreadsheetCell
{
private:
    std::optional<std::string> m_value;

public:
    StringSpreadsheetCell() = default;
    StringSpreadsheetCell(const DoubleSpreadsheetCell& cell)
        : m_value{cell.getString()}
    {}

    void        set(std::string_view value) override { m_value = value; }
    std::string getString() const override { return m_value.value_or(""); }
};


class DoubleSpreadsheetCell : public SpreadsheetCell
{
private:
    std::optional<double> m_value;

public:
    virtual void set(double value) { m_value = value; }
    void         set(std::string_view value) override { m_value = stringToDouble(value); }
    std::string  getString() const override
    {
        return (m_value.has_value() ? doubleToString(m_value.value()) : "");
    }

private:
    static std::string doubleToString(double value);
    static double      stringToDouble(std::string_view value);
};

#include <memory>
#include <vector>


using namespace std;

void test()
{
    vector<unique_ptr<SpreadsheetCell>> cellArray;

    cellArray.push_back(make_unique<StringSpreadsheetCell>());
    cellArray.push_back(make_unique<StringSpreadsheetCell>());
    cellArray.push_back(make_unique<DoubleSpreadsheetCell>());

    DoubleSpreadsheetCell myDbl;
    myDbl.set(8.4);
    StringSpreadsheetCell result{myDbl + myDbl};
}

StringSpreadsheetCell operator+(const StringSpreadsheetCell& lhs, const StringSpreadsheetCell& rhs)
{
    StringSpreadsheetCell newCell;
    newCell.set(lhs.getString() + rhs.getString());
    return newCell;
}
