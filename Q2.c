#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets);

int main(){
    int fuel,consumption,recharge,solarBonus,totalPlanets;
    
    printf("Enter initial fuel: ");
    scanf("%d", &fuel);

    printf("Consumption of fuel from one planet to another planet: ");
    scanf("%d", &consumption);

    printf("Gravitational recharge: ");
    scanf("%d", &recharge);

    printf("Enter Solar bonus: ");
    scanf("%d", &solarBonus);

    printf("Enter Total planets: ");
    scanf("%d", &totalPlanets);

    calculateFuel(fuel, consumption, recharge, solarBonus, 1, totalPlanets);
    return 0;
}

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets)
{
    if (fuel <= 0)
    {
        printf("Fuel exausted\n");
        return;
    }
    else if (planet > totalPlanets)
    {
        printf("Journey completed\n");
        return;
    }
    
    printf("Plane %d, Fuel remaining %d\n", planet, fuel);
    
    fuel -= consumption;
    fuel += recharge;

    if (planet % 4 == 0)
    {
        fuel += solarBonus;
    }
    
    calculateFuel(fuel, consumption, recharge, solarBonus, planet+1, totalPlanets-1);
}