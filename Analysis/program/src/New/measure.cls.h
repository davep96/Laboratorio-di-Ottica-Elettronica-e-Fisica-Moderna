class measure{
	public:
	measure(double val=0, double err=0)
	{
		value = val;
		error = err;
	}
	~measure(){};
	void add(double val, double err)
	{
		value = val;
		error = err;
	}

	double value;
	double error;
};