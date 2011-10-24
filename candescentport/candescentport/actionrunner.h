#ifndef ACTIONRUNNER_H
#define ACTIONRUNNER_H

class ActionRunner //this auto calls things in other objects, using a new thread for each actionrunner.
{
public:

	void (*func)();
	void (*func1)();

	bool run;

	ActionRunner(void* a){
		DataSourceBase* b = a;

		func = funca;
	}

	ActionRunner(void(*funca)(), void(*func1b)()){
		func = funca;
		func1 = func1b;
	}


	bool IsRunning() {
		//return run;
	}

	void Start() {
		run = true;
		Run();

	}

	void Stop() {
		//run = false;
	}

	void Run(){
		//while(run) 
		//{
			func();
		//}
			run = false;
		func1();
	}

};

#endif 