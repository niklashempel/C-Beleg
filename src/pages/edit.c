#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/models.h"
#include "../lib/database.h"
#include "../lib/htmlHelper.h"
#include "../lib/query.h"

int main()
{
    int id = getIdFromQueryString();
    
    Medium medium;
    if (!dbFind(id, &medium))
    {
        printHeader("Edit");
        printf("\
        <form action='/update?id=%d' method='post'>\
            <div class='form-group'>\
                <label for='inputName'>Name</label>\
                <input type='text' class='form-control' id='inputName' placeholder='Enter medium name' name='name' value='%s'>\
            </div>\
            <div class='form-group'>\
                <label for='selectType'>Select medium type</label>\
                <select class='form-control' id='selectType' name='type'>\
                <option value='0' %s>Book</option>\
                <option value='1' %s>CD</option>\
                <option value='2' %s>DVD</option>\
                </select>\
            </div>\
            <div class='form-group'>\
                <label for='inputCreator'>Author/Interpreter</label>\
                <input type='text' class='form-control' id='inputCreator' placeholder='Enter author, interpreter etc.' name='creator' value='%s'>\
            </div>\
            <div class='form-group'>\
                <label for='inputBorrower'>Borrower</label>\
                <input type='text' class='form-control' id='inputBorrower' placeholder='Enter borrower' name='borrower' value='%s'>\
            </div>\
            <button type='submit' class='btn btn-primary'>Submit</button>\
        </form>",
               medium.id, medium.name, medium.type == 0 ? "selected" : "", medium.type == 1 ? "selected" : "", medium.type == 2 ? "selected" : "", medium.creator, medium.borrower);

        printFooter();
    };
    return 0;
}