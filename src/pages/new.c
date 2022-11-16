#include <stdio.h>
#include "../lib/htmlHelper.h"

int main()
{
    printHeader("New");
    puts("\
        <form action='/create' method='post'>\
            <div class='form-group'>\
                <label for='inputName'>Name</label>\
                <input type='text' class='form-control' id='inputName' placeholder='Enter medium name' name='name'>\
            </div>\
            <div class='form-group'>\
                <label for='selectType'>Select medium type</label>\
                <select class='form-control' id='selectType' name='type'>\
                <option value='0'>Book</option>\
                <option value='1'>CD</option>\
                <option value='2'>DVD</option>\
                </select>\
            </div>\
            <div class='form-group'>\
                <label for='inputCreator'>Author/Interpreter</label>\
                <input type='text' class='form-control' id='inputCreator' placeholder='Enter author, interpreter etc.' name='creator'>\
            </div>\
            <div class='form-group'>\
                <label for='inputBorrower'>Borrower</label>\
                <input type='text' class='form-control' id='inputBorrower' placeholder='Enter borrower' name='borrower'>\
            </div>\
            <button type='submit' class='btn btn-primary'>Submit</button>\
        </form>");
    printFooter();

    return 0;
}