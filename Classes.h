//Here are the libraries that we'll need for this code.

//Input/output stream library header file.
#include <iostream>

//File stream library header file.
#include <fstream>

//C libary for additional input and output operations.
#include <cstdio>

//C standard libary needed to use some specific functions.
#include <cstdlib>

//String libary header file.
#include <string>

//Math library header file.
#include <cmath>

//String stream library header file.
#include <sstream>

//Using the namespace standard so I don't need to repeat calling std:: everytime
//I use certain commands.
using namespace std;

//This is the base class that will store all the dose data and relevant fields all
//at once.
class DoseData{
protected:
    //declare several arrays of patient dose data on the heap.  These arrays
    //will store the columns of dose data as strings.
    //These data are protected because they are sensitive patient data.
    string* height_data;
    string* weight_data;
    string* contrast_vol;
    string* fluoro_time;
    string* total_DAP;
    string* Air_Kerma;
    string* Procedure_Time;
    string lines;
    int numlines;

public:
    //Had to save excel file as tab delimited text file, so it could be read in properly.
    //Open up a file stream variable to read in the text file containing the data.
    ifstream data_file;

    //This is the default constructor prototype for the DoseData class.
    DoseData();

    //Copy constructor prototype for the class.  Need a seperate copy constructor because
    //class contains dynamic memory members.  Want to do a deep copy of
    //data that the pointers point to.
    DoseData(const DoseData&);

    //Default destructor prototype for the DoseData class.
    ~DoseData();

    //The following function is used to calculate the sample mean from the dose data.
    //The dose data is an input arguement.  This arguement is an array of data and could be
    //anything related to dose, procedure time and patient height or weight.  Since arrays are
    //passed by reference by default, can use as is.  The array of data is passed as a constant
    //arguement see this function won't change it.  The function returns a float, which is the
    //mean value of the data array.  This function is constant because it doesn't modify class
    //members.  This is just the function prototype.
    float average(const string[]) const;

    //This function calculates the standard deviation from an array of dose data.  The array is passed
    //as an input arguement, but the mean value of the data, calculated from the previous function
    //is passed by reference as an arguement as well.  Since these arguements won't be modified by the
    //function, they have been declared constant arguements.  The standard deviation is returned as
    //a float output argument.  This function is constant because it doesn't modify class members.
    float std_dev( const string[], float&) const;

    //Get the sample standard error of the mean for all the different values.
    float std_err(const string[], float&) const;

    //Get functions needed to get access to all the protected data members in the class.
    //These functions have been declared constant because they do not modify class members.
    string* getHeightData()const { return height_data;}
    string* getWeightData()const { return weight_data;}
    string* getContrastVol()const { return contrast_vol;}
    string* getFluoroTime()const { return fluoro_time;}
    string* getTotalDAP()const { return total_DAP;}
    string* getAirKerma()const { return Air_Kerma;}
    string* getProcedureTime()const { return Procedure_Time;}
    int getNumLines() const {return numlines;}
};


//This is a derived class that inherits from the DoseData class.
//This class will use data from the DoseData class to calculate
//dose rate values, include DAP per unit of fluoro time,
//DAP per unit of procedure time, air kerma per unit of fluoro time
//and air kerma per unit of procedure time.
class DoseRateData: public DoseData{
protected:

    //These variables store the various dose rate values of interest
    //as data arrays.
    string* DAP_per_FluoroTime;
    string* AK_per_FluoroTime;
    string* DAP_per_ProcedureTime;
    string* AK_per_ProcedureTime;

    //To be able to use average and std_dev fucntions of the base class,
    //need to have the above variables as floats first to calculate dose rates.
    //Afterwards, these data can be converted back to string arrays.
    float* DAP_per_FluoroTime_f;
    float* AK_per_FluoroTime_f;
    float* DAP_per_ProcedureTime_f;
    float* AK_per_ProcedureTime_f;

    //Need output string stream buffers to be able to convert the float data
    //back to string data, so that the base class statistical functions can be used
    //on the dose rate data.
    ostringstream* DAP_fluoro_buffer;
    ostringstream* AK_fluoro_buffer;
    ostringstream* DAP_procedure_buffer;
    ostringstream* AK_procedure_buffer;

public:
    //Constructor prototype
    DoseRateData();

    //Destructor prototype
   ~DoseRateData();

    //Copy constructor prototype.
    DoseRateData(const DoseRateData&);

//This function converts the dose data to float values, then divides dose by time to get dose rates,
//Then puts these dose rate values into arrays which are converted back to strings.  The data is
//given as arguements to the function in string and float form, and the dose, time and buffer arrays
//are also given as input arguements to the function.  The prototype is given for this function.
void FloatToString(float[], string[], string[], string[],ostringstream[]);

    //Get functions needed to get access to all the protected data members in the class.
    //These functions have been declared constant because they do not modify class members.
    string* getDAP_per_FluoroTime()const { return DAP_per_FluoroTime;}
    string* getAK_per_FluoroTime()const { return AK_per_FluoroTime;}
    string* getDAP_per_ProcedureTime()const { return DAP_per_ProcedureTime;}
    string* getAK_per_ProcedureTime()const { return AK_per_ProcedureTime;}
};

//The following class will store the statistical analysis of all the data and
//have the ability to send these statistical results to an output file.
class OutputDataFile: public DoseRateData{
private:

    //Averages of all the values of interest.
    float* average_height;
    float* average_weight;
    float* average_contrast;
    float* average_fluoro_time;
    float* average_DAP;
    float* average_AirKerma;
    float* average_ProcedureTime;
    float* average_DAP_per_FluoroTime;
    float* average_AK_per_FluoroTime;
    float* average_DAP_per_ProcedureTime;
    float* average_AK_per_ProcedureTime;

    //Standard deviations of all the values of interest.
    float* stdev_height;
    float* stdev_weight;
    float* stdev_contrast;
    float* stdev_fluoro_time;
    float* stdev_DAP;
    float* stdev_AirKerma;
    float* stdev_ProcedureTime;
    float* stdev_DAP_per_FluoroTime;
    float* stdev_AK_per_FluoroTime;
    float* stdev_DAP_per_ProcedureTime;
    float* stdev_AK_per_ProcedureTime;

    //Standard errors of all the values of interest.
    float* stderr_height;
    float* stderr_weight;
    float* stderr_contrast;
    float* stderr_fluoro_time;
    float* stderr_DAP;
    float* stderr_AirKerma;
    float* stderr_ProcedureTime;
    float* stderr_DAP_per_FluoroTime;
    float* stderr_AK_per_FluoroTime;
    float* stderr_DAP_per_ProcedureTime;
    float* stderr_AK_per_ProcedureTime;


public:
//Default constructor prototype for this class.
OutputDataFile();

//Default destructor prototype for this class.
~OutputDataFile();

//Copy constructor prototype.
OutputDataFile(const OutputDataFile&);

//Function prototype to send statistical data to an output file.
void SendToTextFile();
};
