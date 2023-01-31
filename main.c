

/////////// Observer pattern
/*
Observer is a behavioral 
design pattern that lets 
you define a subscription 
mechanism to notify multiple 
objects about any events that 
happen to the object they’re observing.
*/ 

#include <stdio.h>

#define MAX_NO_OF_OBSERVERS 10u

typedef struct 
{
    /* data */
    int lightLevel;
    int fogLevel;
    int rainLevel;
}t_lightingData;

typedef void(*pFnctPtrObserver)(const t_lightingData lightingData);

static pFnctPtrObserver observerList[MAX_NO_OF_OBSERVERS] = {NULL};

void updateHeadLights(const t_lightingData newLightingData)
{
    if(newLightingData.lightLevel > 50u)
    {
        printf("Headlights turned on\n");
    }
    else{
        printf("Headlights turned off\n");
    }
}

void updateFogLights(const t_lightingData newLightingData)
{
        if(newLightingData.fogLevel > 50u)
    {
        printf("fog lights turned on\n");
    }
    else{
        printf("fog lights turned off\n");
    }
}

void updateRainsensors(const t_lightingData newLightingData)
{
        if(newLightingData.rainLevel > 50u)
    {
        printf("Rain sensors turned on\n");
    }
    else{
        printf("Rain sensors turned off\n");
    }
}

static t_lightingData lightingData = {.lightLevel = 0u, .fogLevel = 0u, .rainLevel=0u};

static void notifyLightingData(void)
{
    for(int i = 00u; i < MAX_NO_OF_OBSERVERS ; i++)
    {
        if(observerList[i] !=NULL)
        {
            observerList[i](lightingData);
        }
    }
}

static void updateLightingData(t_lightingData newLightingData)
{
    lightingData = newLightingData;

    notifyLightingData();
}

static void registerObserver(const pFnctPtrObserver pObserverFcnt)
{
    int obsIdx = 0u;
    while((observerList[obsIdx] != NULL)&&(obsIdx < MAX_NO_OF_OBSERVERS))
    {
        obsIdx++;
    }
    printf("registering Observer %d\n",obsIdx+1u);
    observerList[obsIdx] = pObserverFcnt;
}
static void deregisterObserver(const pFnctPtrObserver pObserverFcnt)
{
    for (int obsIdx = 0u; obsIdx < MAX_NO_OF_OBSERVERS; obsIdx++)
    {
        /* code */
        if(observerList[obsIdx] == pObserverFcnt)
        {
            printf("Deregistering Observer %d\n",obsIdx+1u);
            observerList[obsIdx] = NULL;
            break;
        }
    }
    
}

int main(void)
{
    registerObserver(updateHeadLights);
    registerObserver(updateFogLights);
    registerObserver(updateRainsensors);

    const t_lightingData newLightingData = {.lightLevel = 60u,.fogLevel= 70u,.rainLevel = 80u};
    updateLightingData(newLightingData);


    deregisterObserver(updateHeadLights);
    deregisterObserver(updateFogLights);
    deregisterObserver(updateRainsensors);

    return 0;
}
