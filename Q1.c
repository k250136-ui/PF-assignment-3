#include <stdio.h>

double calculateRepayment(double loan, double interestRate, int years);

int main() {
    double loan;
    int years;

    printf("Loan amount: ");
    scanf("%lf", &loan);

    printf("Years: ");
    scanf("%d", &years);

    double interestRate = 0.05;

    calculateRepayment(loan, interestRate, years);

    return 0;
}

double calculateRepayment(double loan, double interestRate, int years) {

    if (loan <= 0 || years == 0) {
        return loan;
    }
    int currentYear = years;  
    double installment = loan / years;
    loan -= installment;
    loan += loan * interestRate;
    printf("Year %d: Remaining loan = %.2lf\n", currentYear, loan);

    return calculateRepayment(loan, interestRate, years - 1);
}
