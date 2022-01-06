#define boolean		unsigned char
#define true		0x01
#define false		0x00

/*
** Days of the week...
*/
#define MONDAY		 0
#define TUESDAY		 1
#define WEDNESDAY	 2
#define THURSDAY	 3
#define FRIDAY		 4
#define SATURDAY 	 5
#define SUNDAY		 6

/*
** Months...
*/
#define JANUARY		 1
#define FEBRUARY	 2
#define MARCH		 3
#define APRIL		 4
#define MAY			 5
#define JUNE		 6
#define JULY		 7
#define AUGUST		 8
#define SEPTEMBER	 9
#define OCTOBER		 10
#define NOVEMBER	 11
#define DECEMBER	 12

#define DAYS_PER_YEAR	 365

/*
** Reference point is 1st Jan 2008...
*/
#define REFERENCE_YEAR	 2008
#define REFERENCE_MONTH	 JANUARY
#define REFERENCE_DAY	 TUESDAY

#define BASE_YEAR		 1582

/*
** Function declarations...
*/
boolean	        isLeapYear(int year);
void	        printMonth(int month, int year, int daysInMonth, int firstDay);
const char	*   getMonthName(int month);
int		        getDaysPerMonth(int month, int year);
boolean         validate(int month, int year);
int		        calculateFirstDayOfMonth(int month, int year);
int		        addDays(int day, int daysToAdd);
int		        subtractDays(int day, int daysToSubtract);
