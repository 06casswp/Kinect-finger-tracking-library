class ActionRunner //this auto calls things in other objects, will need to be replaced!
{
public:
	Action action;
	Action afterStopAction;

	Thread thread;
	bool run;

	ActionRunner(Action action);

	ActionRunner(Action action, Action afterStopAction)
		: this(action);

	bool IsRunning();


	void Run();
};