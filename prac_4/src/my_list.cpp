#include "my_list.h"
#include <QDebug>

MyList::MyList()
{
}

QString MyList::getValue()
{
   QString ans = "", tmp_str = "";
   for (int i = 0; i < list.size(); ++i)
   {
      tmp_str = list[i];
      if (i > 0)
         ans.append(", ");
      else
         tmp_str[0] = tmp_str[0].toUpper();
      ans.append(tmp_str);
   }
   return ans;
}

void MyList::add_string(QString new_string)
{
   if (new_string.size() == 0)
      return;

   list.append(new_string.toLower());
   emit valueChanged();
}

void MyList::remove_string()
{
   if (list.isEmpty())
      return;

   list.removeLast();
   emit valueChanged();
}
