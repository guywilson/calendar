#define boolean		unsigned char
#define true		0x01
#define false		0x00

/*
** Days of the week...
*/
#define SUNDAY		 0
#define MONDAY		 1
#define TUESDAY		 2
#define WEDNESDAY	 3
#define THURSDAY	 4
#define FRIDAY		 5
#define SATURDAY 	 6

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

#define WEEK_START_DAY   SUNDAY
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
