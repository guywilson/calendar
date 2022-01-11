#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef C64
#include "c64.h"
#endif

#include "calendar.h"

/*******************************************************************************
*
* int main(int argc, char *argv[]);
*
* Entry point of program, command line arguments passed in through argv array
*
*******************************************************************************/
int main(int argc, char *argv[])
{
	char *		pszYear;
	char *		pszMonth;
	int 		year;
	int 		month;
	int 		firstDay;
	int			daysPerMonth;
	
	/*
	** Fetch parameters...
	*/
	if (argc == 3) {
		pszMonth = strdup(argv[1]);
		pszYear = strdup(argv[2]);
	}
	else {
		pszMonth = (char *)malloc(8);
		pszYear = (char *)malloc(8);

		printf("Please enter month number (1 - 12): ");
		fgets(pszMonth, 8, stdin);

		printf("Please enter year (yyyy): ");
		fgets(pszYear, 8, stdin);
	}
	
	month = (int)strtol(pszMonth, NULL, 10);
	year = (int)strtol(pszYear, NULL, 10);
	
	free(pszMonth);
	free(pszYear);

	/*
	** Do some validation...
	*/
	if (!validate(month, year)) {
		return -1;
	}
	
	/*
	** Calculate the 1st day of the given month...
	*/
	firstDay = calculateFirstDayOfMonth(month, year);

	daysPerMonth = getDaysPerMonth(month, year);
	
	/*
	** Print the calendar...
	*/
	printMonth(month, year, daysPerMonth, firstDay);

	return 0;
}


/*******************************************************************************
*
* int calculateFirstDayOfMonth(int month, int year);
*
* Calculates which day of the week the 1st of the given month falls on. This
* is calculated with reference to a known date - 1st January 2008 which was a
* Tuesday.
*
*******************************************************************************/
int calculateFirstDayOfMonth(int month, int year)
{
	int firstDay = REFERENCE_DAY;
	int yearCounter = 0;
	int monthCounter = JANUARY;
	int daysInMonth = 0;
	
	/*
	** The following algorithm works as we know that
	** January 1st will move on one day each year, and
	** two for a leap year...
	*/
	if (year >= REFERENCE_YEAR) {
		/*
		** We're counting forwards...
		*/
		for (yearCounter = REFERENCE_YEAR;yearCounter < year;yearCounter++) {
			if (isLeapYear(yearCounter)) {
				firstDay = addDays(firstDay, 2);
			}
			else {
				firstDay = addDays(firstDay, 1);
			}
		}
	}
	else {
		/*
		** Counting backwards...
		*/
		for (yearCounter = REFERENCE_YEAR - 1;yearCounter >= year;yearCounter--) {
			if (isLeapYear(yearCounter)) {
				firstDay = subtractDays(firstDay, 2);
			}
			else {
				firstDay = subtractDays(firstDay, 1);
			}

		}
	}

	/*
	** Now get to the month we want...
	*/
	monthCounter = JANUARY;
	
	while (monthCounter < month) {
		daysInMonth = getDaysPerMonth(monthCounter, year);
		firstDay = addDays(firstDay, (daysInMonth - 28));
		
		monthCounter++;
	}
	
	return firstDay;
}


/*******************************************************************************
*
* void printMonth(int month, int year, int daysInMonth, int firstDay);
*
* Print the calendar for the requested month to the screen.
*
*******************************************************************************/
void printMonth(int month, int year, int daysInMonth, int firstDay)
{
	int			dayOfWeekCounter;
	int 		dayOfMonthCounter = 1;
	int 		i;
	int			dayCount;
	
	printf("\n\n\t%s %d\n\n", getMonthName(month), year);
	
	/*
	** First draw the days...
	*/
	printf("\t");

	dayCount = 0;
	i = WEEK_START_DAY;

	while (dayCount < 7) {
		printf("   %c", getWeekDayChar(i));

		i++;

		if (i == 7) {
			i = 0;
		}

		dayCount++;
	}

	printf("\n");
	printf("\t----------------------------\n");
	
	dayOfWeekCounter = firstDay;
	
	printf("\t  ");
	
	for (i = 0;i < dayOfWeekCounter;i++) {
		printf("    ");
	}

	while (dayOfMonthCounter <= daysInMonth) {
		if (dayOfMonthCounter < 10) {
			printf(" ");
		}
		
		printf("%d  ", dayOfMonthCounter);
		
		if (dayOfWeekCounter++ == 6) {
			dayOfWeekCounter = 0;
			printf("\n\t  ");
		}
		
		dayOfMonthCounter++;
	}
	
	printf("\n\n");
}


/*******************************************************************************
*
* char * getMonthName(int month);
*
* Return the month name for the given integer month constant.
*
*******************************************************************************/
const char * getMonthName(int month)
{
	static const char * months[] = {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	return months[month - 1];
}

char getWeekDayChar(int weekDay)
{
	const char 	days[7] = {'S', 'M', 'T', 'W', 'T', 'F', 'S'};

	return days[weekDay];
}

/*******************************************************************************
*
* boolean isLeapYear(int year);
*
* Returns true if the given year is a leap year, the basis of the
* Gregorian calendar system.
*
*******************************************************************************/
boolean isLeapYear(int year)
{
	return (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0) ? true : false;
}


/*******************************************************************************
*
* int getDaysPerMonth(int month, int year);
*
* Returns the number of days in the given month, the only variation being for
* February depending on whether the given year is a leap year.
*
*******************************************************************************/
int getDaysPerMonth(int month, int year)
{
	static const int days_per_month[] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	
	int days = 0;

	days = days_per_month[month - 1];
	
	if (month == FEBRUARY) {
		if (isLeapYear(year)) {
			days += 1;
		}
	}
	
	return days;
}


/*******************************************************************************
*
* boolean validateGregorian(int month, int year);
*
* Validate that the given month and year are valid and are after the Gregorian
* calendar system was adopted.
*
*******************************************************************************/
boolean validate(int month, int year)
{
	boolean isValid = true;
	
	if (month > 12 || month < 1) {
		printf("\n\nInvalid month, must be between 1 and 12\n");
		isValid = false;
	}
	
	if (year < BASE_YEAR || (year == BASE_YEAR && month < MARCH)) {
		printf("\n\nGregorian calendar started 24th Feb 1582 so therefore the \nrequested month and year must be after February 1582.\n");
		isValid = false;
	}
	
	return isValid;
}


/*******************************************************************************
*
* int addDays(int day, int daysToAdd);
*
* Adds the specified number of days to the given day to return the day of the
* week.
*
*******************************************************************************/
int addDays(int day, int daysToAdd)
{
	int i;
	
	for (i = 0;i < daysToAdd;i++) {
		day++;
		
		if (day > 6) {
			day = 0;
		}
	}
	
	return day;
}


/*******************************************************************************
*
* int subtractDays(int day, int daysToSubtract);
*
* Subtracts the specified number of days from the given day to return the day 
* of the week.
*
*******************************************************************************/
int subtractDays(int day, int daysToSubtract)
{
	int i;
	
	for (i = 0;i < daysToSubtract;i++) {
		day--;
		
		if (day < 0) {
			day = 6;
		}
	}
	
	return day;
}
