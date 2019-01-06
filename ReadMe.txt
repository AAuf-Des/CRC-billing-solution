CRC PROJECT 
SEBASTIAN PERSSON
______________________________________________________
void setInvoiceMonths()

//2628000   is the average amount of seconds on a month (includeing leapyears and such).
//the reason i set turn "first" date into a struc tm, set the month day to 15 and then back to temp month is so that if first date in cdr 
//happend to be Month day 01 it could mess upp the entire month system in the program.
//if i set day to 15 and then convert the struc tm back to time_t, the program always have a few days it can diff.
//example if the first date we got is the first day of a month with less than average days.


_________________________________________________________
yearMonthValue

is a value i came up with to simplify comparing dates and months, it might seem strange at first but as we dont need to compare
any month days i felt like this was the best way to compare dates.

for example in void assignCallsToInvoices(); we had to compare Months and years and phonenumber. if we wouldve used struc tm 
to compare these dates we would have to check if "years are the same" and "month are the same" and "numbers are the same" and 
none of the other values in struc tm such as day(witch is irrelevent to the invoice) are diffrent.
______________________________________________________