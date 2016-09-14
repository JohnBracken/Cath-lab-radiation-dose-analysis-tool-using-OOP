//The following program is designed to read in patient radiation dose data
//From an Excel file that has been converted to a tab delimited
//text file.  Once the data has been read in, the mean and standard
//deviation of these data are calculated using functions.
//This code will give us a sense of what kind of doses and procedure times
//coronary patients have been experiencing in the cath lab over the past 3
//years or so.  This code makes use of object oriented programming and
//classes.

//File containing the classes needed to execute this code.
#include "Classes.h"


//Default constructor definition for DoseData class.
DoseData::DoseData()
{
    //Open the data file variable to enable reading in the data text file.
    data_file.open("Qry_Air_Kerma_withtimes.txt");

    //The following code section will determine the number of lines that are present
    //in the file and how many lines need to be read in.


    //Initialize the number of lines in the file to zero.
    numlines = 0;

    //Get the first line of the file and put it into lines variable, so that
    //the while loop will be able to check it right away at the start of the loop.
     getline(data_file, lines);

    //From here on in, check the beginning of each line in the file by
    //looking at the first character.  If the first character
    //is not equal to a space, then get the line and
    //increment the number of lines.  Keep doing this until a
    //space is reached at the beginning of the line, which indicates that
    //the end of the data file has been reached.
    while(lines.substr(0,1) != ""){
    ++numlines;
    getline(data_file, lines);
    }

    //Clear the end-of-file indicator using the clear function.
    data_file.clear();

    //Go back to the beginning of the file using the seekg function.
   data_file.seekg(0, ios::beg);

    //Declare dose data arrays on the heap as strings for data storage.
    height_data = new string[numlines];
    weight_data = new string[numlines];
    contrast_vol = new string[numlines];
    fluoro_time = new string[numlines];
    total_DAP = new string[numlines];
    Air_Kerma = new string[numlines];
    Procedure_Time = new string[numlines];


    //Read in the data text file by going through each line in the file
    //one at a time.
    for(int i = 0; i < numlines; ++i)
        {
         //The >> operator delimits the data in the text file, so each array will
         //be given its correct value as they fill up simultaneously.
         data_file >> height_data[i] >> weight_data[i] >> contrast_vol[i]
         >> fluoro_time[i] >> total_DAP[i] >> Air_Kerma[i] >> Procedure_Time[i];

        }
        cout << "DoseData constructor called." << endl;
}

//Copy constructor definition for the DoseData class
DoseData::DoseData(const DoseData& first){
    //Notification of copy constructor being invoked.
        cout << "DoseData copy constructor called." << endl;

        //Generate copies of lines and numlines variables.
        //For a copy constructor, don't need to copy the class
        //functions, just the members.
        lines = first.lines;
        numlines = first.numlines;

        //Generate copies of all the dose data.  Size of each array is numlines.
        //All these data need to be declared on the heap.
        height_data = new string[first.numlines];
        weight_data = new string[first.numlines];
        contrast_vol = new string[first.numlines];
        fluoro_time = new string[first.numlines];
        total_DAP = new string[first.numlines];
        Air_Kerma = new string[first.numlines];
        Procedure_Time = new string[first.numlines];


    //Initialize all the copied arrays of data, with the data from the original class instance.
    for(int i=0; i < numlines; ++i)
        {
             height_data[i] = first.height_data[i];
             weight_data[i] = first.weight_data[i];
             contrast_vol[i] = first.contrast_vol[i];
             fluoro_time[i] = first.fluoro_time[i];
             total_DAP[i] = first.total_DAP[i];
             Air_Kerma[i] = first.Air_Kerma[i];
             Procedure_Time[i] = first.Procedure_Time[i];
        }
}

//Default destructor definition for the DoseData class.
DoseData::~DoseData()
{
//delete the arrays of data from the heap after using them.
    delete[] height_data;
    delete[] weight_data;
    delete[] contrast_vol;
    delete[] fluoro_time;
    delete[] total_DAP;
    delete[] Air_Kerma;
    delete[] Procedure_Time;

    //Assign data array pointers to a NULL value to avoid memory problems
    //and crashes.  Pointer no longer points to anything so memory is freed up.
    height_data = NULL;
    weight_data = NULL;
    contrast_vol = NULL;
    fluoro_time = NULL;
    total_DAP = NULL;
    Air_Kerma = NULL;
    Procedure_Time = NULL;

    //Close the data file after using it to free up memory again.
    data_file.close();

    //Notification that destructor has been invoked.
    cout << "DoseData destructor called." << endl;
}


//Function definition to calculate the average of a dataset in the DoseData class.
float DoseData:: average(const string data[]) const
 {
 //Variable to keep a running total of the some of the data values in the array.
    //Make it a local variable to confine it to this function.
    float tally = 0;

    //Variable to keep track of how many data values have been added together.
    int counter = 0;

    //Variable used to store the mean value of all the data in the array passed to the
    //function.
    float average;


    //Loop through all the data in the array to add it all together and to keep track
    //of the number of values being added together.  The loop starts at position 1,
    //because position zero contains only the label of what the data is, which we don't
    //want to include in the sum.
    for (int i = 1; i<numlines; ++i)
    {
        //Check to see if a value in the data array actually contains a number and not
        //the world "null", which means that no value is present in that position.
        if(data[i] != "null")
            {
            //If a number is present at this position in the array, then add this current
            //number to the total sum.  The "atof" function converts the number in the array
            //(which was originally a string) into a float, so that the sum operation can be
            //performed.  The c-str() function is called on the data string element to convert
            //the data string value from a C++ string to a C type string, since the "atof"
            //only works on c-style strings.
            tally += atof(data[i].c_str());

            //Increment the data counter, indicating that a number value is present at this
            //position.
            ++counter;
            }
    }
    //After going through the entire array and adding all the numbers together, calculate the mean value
    //of the data in the array.  Counter needs to be converted to a float to do the arithmetic properly.
    average = tally/static_cast<float>(counter);

//Return the mean value.
return average;
 }


//Function definition to calculate standard deviation of a dataset in the DoseData class.
float DoseData:: std_dev( const string data[], float &average_val) const
{
//A standard deviation requires a summation as well of the differences between each data
        //point and the mean value of the data.  This variable keeps track of the sum.
         float tally = 0;

         //A counter is used an incremented every time a numerical value is detected at a position
         //in the array.
         int counter = 0;

         //The variable used to store variance, which is just the square of standard deviation.
         float variance;

         //The variable used to store standard deviation.
         float standard_dev;

        //Carry out the summation of the data points in the array for the standard deviation
        //using a loop.  The loops starts a position 1, because position 0 contains the label
        //for the data, which we don't want to include in the sum.
        for (int i = 1; i<numlines; ++i)
        {
        //Again, check to make sure that the current position in the array contains a number.
        if(data[i] != "null")
            {
            //If a number is present in the current position, add the summation term for this
            //position to the total sum.  The summation term is the square of the difference
            //between the current value in the array and the mean value of the data.  The
            //difference is squared using the power function "pow" from the cmath library.
            tally += pow(atof(data[i].c_str()) - average_val,2);

            //Increment the counter value indicating that a number was present at the current
            //position.
            ++counter;
            }
        }

        //After the summation of the datapoints is complete, calculate the variance.
        //This is the formula for variance, which you can find in a textbook.
        //The counter value has to be cast to be a float for the calculation.
        variance = tally/static_cast<float>(counter-1);

        //The standard deviation is just the square root of the variance, which is returned
        //by the function.
        standard_dev = sqrt(variance);
        return standard_dev;
}

//Function definition to calculate standard deviation of a dataset in the DoseData class.
float DoseData:: std_err( const string data[], float &average_val) const
{
//A standard deviation requires a summation as well of the differences between each data
        //point and the mean value of the data.  This variable keeps track of the sum.
         float tally = 0;

         //A counter is used an incremented every time a numerical value is detected at a position
         //in the array.
         int counter = 0;

         //The variable used to store variance, which is just the square of standard deviation.
         float variance;

         //The variable used to store standard deviation.
         float standard_dev;

         //The variable used to store the standard error of the mean.
         float std_error;

        //Carry out the summation of the data points in the array for the standard deviation
        //using a loop.  The loops starts a position 1, because position 0 contains the label
        //for the data, which we don't want to include in the sum.
        for (int i = 1; i<numlines; ++i)
        {
        //Again, check to make sure that the current position in the array contains a number.
        if(data[i] != "null")
            {
            //If a number is present in the current position, add the summation term for this
            //position to the total sum.  The summation term is the square of the difference
            //between the current value in the array and the mean value of the data.  The
            //difference is squared using the power function "pow" from the cmath library.
            tally += pow(atof(data[i].c_str()) - average_val,2);

            //Increment the counter value indicating that a number was present at the current
            //position.
            ++counter;
            }
        }

        //After the summation of the datapoints is complete, calculate the variance.
        //This is the formula for variance, which you can find in a textbook.
        //The counter value has to be cast to be a float for the calculation.
        variance = tally/static_cast<float>(counter-1);

        //The standard deviation is just the square root of the variance, which is returned
        //by the function.
        standard_dev = sqrt(variance);

        //Calculate the standard error of the mean.
        std_error = standard_dev/sqrt(static_cast<float>(counter));

        //Return the value for the stnadard error.
        return std_error;
}

//Constructor for the DoseRateData class.
DoseRateData::DoseRateData()
{
        //Allocate string and float arrays for the dose rate data
        //on the heap.  Also allocate the string buffers on the heap.
        DAP_per_FluoroTime = new string[numlines];
        AK_per_FluoroTime = new string[numlines];
        DAP_per_ProcedureTime = new string[numlines];
        AK_per_ProcedureTime = new string[numlines];

        DAP_per_FluoroTime_f = new float[numlines];
        AK_per_FluoroTime_f = new float[numlines];
        DAP_per_ProcedureTime_f = new float[numlines];
        AK_per_ProcedureTime_f = new float[numlines];

        DAP_fluoro_buffer = new ostringstream[numlines];
        AK_fluoro_buffer = new ostringstream[numlines];
        DAP_procedure_buffer = new ostringstream[numlines];
        AK_procedure_buffer = new ostringstream[numlines];

//Start initializing the arrays of dose rate data, using a function that converts the string
//data arrays to float data, calculates the dose rates, and then reconverts the dose rate arrays
//back to string data.
FloatToString(DAP_per_FluoroTime_f, DAP_per_FluoroTime, total_DAP, fluoro_time, DAP_fluoro_buffer);
FloatToString(AK_per_FluoroTime_f,AK_per_FluoroTime, Air_Kerma, fluoro_time,AK_fluoro_buffer);
FloatToString(DAP_per_ProcedureTime_f,DAP_per_ProcedureTime, total_DAP, Procedure_Time,DAP_procedure_buffer);
FloatToString(AK_per_ProcedureTime_f,AK_per_ProcedureTime, Air_Kerma, Procedure_Time,AK_procedure_buffer);

        cout << "DoseRateData constructor called." << endl;
}

//Destructor for the DoseRateData class.
DoseRateData::~DoseRateData()
{
    //Delete all pointers to data on the heap.
    delete[] DAP_per_FluoroTime;
    delete[] AK_per_FluoroTime;
    delete[] DAP_per_ProcedureTime;
    delete[] AK_per_ProcedureTime;

    delete[] DAP_per_FluoroTime_f;
    delete[] AK_per_FluoroTime_f;
    delete[] DAP_per_ProcedureTime_f;
    delete[] AK_per_ProcedureTime_f;

    delete[] DAP_fluoro_buffer;
    delete[] AK_fluoro_buffer;
    delete[] DAP_procedure_buffer;
    delete[] AK_procedure_buffer;

    //Assign these pointers to null to avoid dangling pointers.
    DAP_per_FluoroTime = NULL;
    AK_per_FluoroTime = NULL;
    DAP_per_ProcedureTime = NULL;
    AK_per_ProcedureTime = NULL;

    DAP_per_FluoroTime_f = NULL;
    AK_per_FluoroTime_f = NULL;
    DAP_per_ProcedureTime_f = NULL;
    AK_per_ProcedureTime_f = NULL;

    DAP_fluoro_buffer = NULL;
    AK_fluoro_buffer = NULL;
    DAP_procedure_buffer = NULL;
    AK_procedure_buffer = NULL;

    cout << "DoseRateData destructor called." << endl;
   }

   //Copy constructor for the DoseRateData class.  Need to include
   //DoseData copy constructor call in the initialization list of
   //the copy constructor definition for this derived class.
   //Initialization list not part of the copy constructor prototype
   //declaration.
DoseRateData::DoseRateData(const DoseRateData &first):DoseData(first)
{
    //Notification of copy constructor being invoked.
        cout << "DoseRateData copy constructor called." << endl;

        //Generate copies of lines and numlines variables.
        //For a copy constructor, don't need to copy the class
        //functions, just the members.

        //Generate copies of all the dose data.  Size of each array is numlines.
        //All these data need to be declared on the heap.  Note that this class
        //inherits all the other data in the base class, so this has to be
        //taken into account.  Don't need the buffers because the original class
        //instance already used them to fill the float and string array datasets.
        DAP_per_FluoroTime = new string[first.numlines];
        AK_per_FluoroTime = new string[first.numlines];
        DAP_per_ProcedureTime = new string[first.numlines];
        AK_per_ProcedureTime = new string[first.numlines];
        DAP_per_FluoroTime_f = new float[first.numlines];
        AK_per_FluoroTime_f = new float[first.numlines];
        DAP_per_ProcedureTime_f = new float[first.numlines];
        AK_per_ProcedureTime_f = new float[first.numlines];


    //Initialize all the copied arrays of data, with the data from the original class instance.
    for(int i=0; i < numlines; ++i)
        {
             DAP_per_FluoroTime[i] = first.DAP_per_FluoroTime[i];
             AK_per_FluoroTime[i] = first.AK_per_FluoroTime[i];
             DAP_per_ProcedureTime[i] = first.DAP_per_ProcedureTime[i];
             AK_per_ProcedureTime[i] = first.AK_per_ProcedureTime[i];
             DAP_per_FluoroTime_f[i] = first.DAP_per_FluoroTime_f[i];
             AK_per_FluoroTime_f[i] = first.AK_per_FluoroTime_f[i];
             DAP_per_ProcedureTime_f[i] = first.DAP_per_ProcedureTime_f[i];
             AK_per_ProcedureTime_f[i] = first.AK_per_ProcedureTime_f[i];
        }
}

//FloattoString function for the data in the DoseRateData class.
//This function converts the dose data to float values, then divides dose by time to get dose rates,
//Then puts these dose rate values into arrays which are converted back to strings.  The data is
//given as arguements to the function in string and float form, and the dose, time and buffer arrays
//are also given as input arguements to the function.  The prototype is given for this function.
void DoseRateData::FloatToString(float data_f[], string data[], string dose[], string time[],ostringstream buffer[])
{
    //Start looking through the data arrays.
    for(int i = 0; i < numlines; ++i){
            //If a value in the dose or time array is not equal to a "null" value, then it will be possible to
            //divide dose by time to get a dose rate value.
            if(dose[i] != "null" && time[i] != "null")
                {
            //Calculate DAP per fluoro time and store in array.  Must convert strings to floats first.
            data_f[i] = (atof(dose[i].c_str()))/(atof(time[i].c_str()));

            //Use the string stream to move the DAP per fluoro time values into a buffer.
            buffer[i] << data_f[i];

            //  Store the buffered data in a string array after converting it from a float to a string.
            data[i] = buffer[i].str();
                }
            else
                {
                    //If one of the data values is "null", then you can't calculate a dose rate.
                    //Therefore, initialize this element to zero.  In the string array of the
                    //data, this element would be initialized to "null".
                    data_f[i] = 0;
                    data[i] = "null";
                }
    }
}

//Default constructor definition for the OutputDataFile class.
OutputDataFile::OutputDataFile()
{
    //Memory allocation for average values.
    average_height = new float;
    average_weight = new float;
    average_contrast = new float;
    average_fluoro_time = new float;
    average_DAP = new float;
    average_AirKerma = new float;
    average_ProcedureTime = new float;
    average_DAP_per_FluoroTime = new float;
    average_AK_per_FluoroTime = new float;
    average_DAP_per_ProcedureTime = new float;
    average_AK_per_ProcedureTime = new float;

    //Memory allocation for standard deviations.
    stdev_height = new float;
    stdev_weight = new float;
    stdev_contrast = new float;
    stdev_fluoro_time = new float;
    stdev_DAP = new float;
    stdev_AirKerma = new float;
    stdev_ProcedureTime = new float;
    stdev_DAP_per_FluoroTime = new float;
    stdev_AK_per_FluoroTime = new float;
    stdev_DAP_per_ProcedureTime = new float;
    stdev_AK_per_ProcedureTime = new float;

    //Memory allocation for standard deviations.
    stderr_height = new float;
    stderr_weight = new float;
    stderr_contrast = new float;
    stderr_fluoro_time = new float;
    stderr_DAP = new float;
    stderr_AirKerma = new float;
    stderr_ProcedureTime = new float;
    stderr_DAP_per_FluoroTime = new float;
    stderr_AK_per_FluoroTime = new float;
    stderr_DAP_per_ProcedureTime = new float;
    stderr_AK_per_ProcedureTime = new float;

    //Use the derived functions from the DoseData and DoseRateData classes
    //to determine the averages and standard deviations
    //for each of the different data types.
    *average_height = average(getHeightData());
    *average_weight = average(getWeightData());
    *average_contrast = average(getContrastVol());
    *average_fluoro_time = average(getFluoroTime());
    *average_DAP = average(getTotalDAP());
    *average_AirKerma = average(getAirKerma());
    *average_ProcedureTime = average(getProcedureTime());
    *average_DAP_per_FluoroTime = average(getDAP_per_FluoroTime());
    *average_AK_per_FluoroTime = average(getAK_per_FluoroTime());
    *average_DAP_per_ProcedureTime = average(getDAP_per_ProcedureTime());
    *average_AK_per_ProcedureTime = average(getAK_per_ProcedureTime());

    *stdev_height = std_dev(getHeightData(), *average_height);
    *stdev_weight = std_dev(getWeightData(), *average_weight);
    *stdev_contrast = std_dev(getContrastVol(), *average_contrast);
    *stdev_fluoro_time = std_dev(getFluoroTime(), *average_fluoro_time);
    *stdev_DAP = std_dev(getTotalDAP(), *average_DAP);
    *stdev_AirKerma = std_dev(getAirKerma(), *average_AirKerma);
    *stdev_ProcedureTime = std_dev(getProcedureTime(), *average_ProcedureTime);
    *stdev_DAP_per_FluoroTime = std_dev(getDAP_per_FluoroTime(), *average_DAP_per_FluoroTime);
    *stdev_AK_per_FluoroTime = std_dev(getAK_per_FluoroTime(), *average_AK_per_FluoroTime);
    *stdev_DAP_per_ProcedureTime = std_dev(getDAP_per_ProcedureTime(), *average_DAP_per_ProcedureTime);
    *stdev_AK_per_ProcedureTime = std_dev(getAK_per_ProcedureTime(), *average_AK_per_ProcedureTime);

    *stderr_height = std_err(getHeightData(), *average_height);
    *stderr_weight = std_err(getWeightData(), *average_weight);
    *stderr_contrast = std_err(getContrastVol(), *average_contrast);
    *stderr_fluoro_time = std_err(getFluoroTime(), *average_fluoro_time);
    *stderr_DAP = std_err(getTotalDAP(), *average_DAP);
    *stderr_AirKerma = std_err(getAirKerma(), *average_AirKerma);
    *stderr_ProcedureTime = std_err(getProcedureTime(), *average_ProcedureTime);
    *stderr_DAP_per_FluoroTime = std_err(getDAP_per_FluoroTime(), *average_DAP_per_FluoroTime);
    *stderr_AK_per_FluoroTime = std_err(getAK_per_FluoroTime(), *average_AK_per_FluoroTime);
    *stderr_DAP_per_ProcedureTime = std_err(getDAP_per_ProcedureTime(), *average_DAP_per_ProcedureTime);
    *stderr_AK_per_ProcedureTime = std_err(getAK_per_ProcedureTime(), *average_AK_per_ProcedureTime);


    cout << "OutputDataFile constructor called." << endl;
}

//Default destructor definition for the OutputDataFile class.
OutputDataFile::~OutputDataFile()
{
//    //Delete all pointers to data on the heap.
    delete average_height;
    delete average_weight;
    delete average_contrast;
    delete average_fluoro_time;
    delete average_DAP;
    delete average_AirKerma;
    delete average_ProcedureTime;
    delete average_DAP_per_FluoroTime;
    delete average_AK_per_FluoroTime;
    delete average_DAP_per_ProcedureTime;
    delete average_AK_per_ProcedureTime;
    delete stdev_height;
    delete stdev_weight;
    delete stdev_contrast;
    delete stdev_fluoro_time;
    delete stdev_DAP;
    delete stdev_AirKerma;
    delete stdev_ProcedureTime;
    delete stdev_DAP_per_FluoroTime;
    delete stdev_AK_per_FluoroTime;
    delete stdev_DAP_per_ProcedureTime;
    delete stdev_AK_per_ProcedureTime;
    delete stderr_height;
    delete stderr_weight;
    delete stderr_contrast;
    delete stderr_fluoro_time;
    delete stderr_DAP;
    delete stderr_AirKerma;
    delete stderr_ProcedureTime;
    delete stderr_DAP_per_FluoroTime;
    delete stderr_AK_per_FluoroTime;
    delete stderr_DAP_per_ProcedureTime;
    delete stderr_AK_per_ProcedureTime;


    //Assign these pointers to null to avoid dangling pointers and memory problems.
    average_height = NULL;
    average_weight = NULL;
    average_contrast = NULL;
    average_fluoro_time = NULL;
    average_DAP = NULL;
    average_AirKerma = NULL;
    average_ProcedureTime = NULL;
    average_DAP_per_FluoroTime = NULL;
    average_AK_per_FluoroTime = NULL;
    average_DAP_per_ProcedureTime = NULL;
    average_AK_per_ProcedureTime = NULL;
    stdev_height = NULL;
    stdev_weight = NULL;
    stdev_contrast = NULL;
    stdev_fluoro_time = NULL;
    stdev_DAP = NULL;
    stdev_AirKerma = NULL;
    stdev_ProcedureTime = NULL;
    stdev_DAP_per_FluoroTime = NULL;
    stdev_AK_per_FluoroTime = NULL;
    stdev_DAP_per_ProcedureTime = NULL;
    stdev_AK_per_ProcedureTime = NULL;
    stderr_height = NULL;
    stderr_weight = NULL;
    stderr_contrast = NULL;
    stderr_fluoro_time = NULL;
    stderr_DAP = NULL;
    stderr_AirKerma = NULL;
    stderr_ProcedureTime = NULL;
    stderr_DAP_per_FluoroTime = NULL;
    stderr_AK_per_FluoroTime = NULL;
    stderr_DAP_per_ProcedureTime = NULL;
    stderr_AK_per_ProcedureTime = NULL;

    cout << "OutputDataFile destructor called." << endl;
}

//Copy constructor definition for the OutputDataFile class.
//Need to call DoseRateData copy constructor in initialization list.
OutputDataFile::OutputDataFile(const OutputDataFile& test):DoseRateData(test)
{
    //Allocate memory for all the variables.
    average_height = new float;
    average_weight = new float;
    average_contrast = new float;
    average_fluoro_time = new float;
    average_DAP = new float;
    average_AirKerma = new float;
    average_ProcedureTime = new float;
    average_DAP_per_FluoroTime = new float;
    average_AK_per_FluoroTime = new float;
    average_DAP_per_ProcedureTime = new float;
    average_AK_per_ProcedureTime = new float;
    stdev_height = new float;
    stdev_weight = new float;
    stdev_contrast = new float;
    stdev_fluoro_time = new float;
    stdev_DAP = new float;
    stdev_AirKerma = new float;
    stdev_ProcedureTime = new float;
    stdev_DAP_per_FluoroTime = new float;
    stdev_AK_per_FluoroTime = new float;
    stdev_DAP_per_ProcedureTime = new float;
    stdev_AK_per_ProcedureTime = new float;
    stderr_height = new float;
    stderr_weight = new float;
    stderr_contrast = new float;
    stderr_fluoro_time = new float;
    stderr_DAP = new float;
    stderr_AirKerma = new float;
    stderr_ProcedureTime = new float;
    stderr_DAP_per_FluoroTime = new float;
    stderr_AK_per_FluoroTime = new float;
    stderr_DAP_per_ProcedureTime = new float;
    stderr_AK_per_ProcedureTime = new float;



    //Copy the data over to the new variables.
    //Since variables were declared as pointers in the heap
    //make sure to copy the values over by dereferencing,
    //using the asterisk.
    *average_height = *test.average_height;
    *average_weight = *test.average_weight;
    *average_contrast = *test.average_contrast;
    *average_fluoro_time = *test.average_fluoro_time;
    *average_DAP = *test.average_DAP;
    *average_AirKerma = *test.average_AirKerma;
    *average_ProcedureTime = *test.average_ProcedureTime;
    *average_DAP_per_FluoroTime = *test.average_DAP_per_FluoroTime;
    *average_AK_per_FluoroTime = *test.average_AK_per_FluoroTime;
    *average_DAP_per_ProcedureTime = *test.average_DAP_per_ProcedureTime;
    *average_AK_per_ProcedureTime = *test.average_AK_per_ProcedureTime;
    *stdev_height = *test.stdev_height;
    *stdev_weight = *test.stdev_weight;
    *stdev_contrast = *test.stdev_contrast;
    *stdev_fluoro_time = *test.stdev_fluoro_time;
    *stdev_DAP = *test.stdev_DAP;
    *stdev_AirKerma = *test.stdev_AirKerma;
    *stdev_ProcedureTime = *test.stdev_ProcedureTime;
    *stdev_DAP_per_FluoroTime = *test.stdev_DAP_per_FluoroTime;
    *stdev_AK_per_FluoroTime = *test.stdev_AK_per_FluoroTime;
    *stdev_DAP_per_ProcedureTime = *test.stdev_DAP_per_ProcedureTime;
    *stdev_AK_per_ProcedureTime = *test.stdev_AK_per_ProcedureTime;
    *stderr_height = *test.stderr_height;
    *stderr_weight = *test.stderr_weight;
    *stderr_contrast = *test.stderr_contrast;
    *stderr_fluoro_time = *test.stderr_fluoro_time;
    *stderr_DAP = *test.stderr_DAP;
    *stderr_AirKerma = *test.stderr_AirKerma;
    *stderr_ProcedureTime = *test.stderr_ProcedureTime;
    *stderr_DAP_per_FluoroTime = *test.stderr_DAP_per_FluoroTime;
    *stderr_AK_per_FluoroTime = *test.stderr_AK_per_FluoroTime;
    *stderr_DAP_per_ProcedureTime = *test.stderr_DAP_per_ProcedureTime;
    *stderr_AK_per_ProcedureTime = *test.stderr_AK_per_ProcedureTime;

    cout << "OutputDataFile copy constructor called." << endl;

}

//Function definition to send all the data to an output file.
void OutputDataFile::SendToTextFile()
{
    //Generate the variable for the output file.
    ofstream OutFile;

    //Open up a textfile
    OutFile.open("DoseData_StatsSummary.txt");

    //Send all the data to the text file one line at a time.
    //Use unicode representation (\u...) to print subscripts,
    //superscripts and other symbols as needed.
    OutFile << "**********Averages**********" << endl
     << '\n'
     << "Average height:" << " " << *average_height << " cm" << endl
     << "Average weight:" << " " << *average_weight << " kg" << endl
     << "Average contrast volume:" << " " << *average_contrast << " ml" << endl
     << "Average fluoro time:" << " " << *average_fluoro_time << " min" << endl
     << "Average dose-area product:" << " " << *average_DAP << " Gy\u00b7cm\u00b2" << endl
     << "Average air kerma:" << " " << *average_AirKerma << " mGy" << endl
     << "Average procedure time:" << " " << *average_ProcedureTime << " min" << endl
     << "Average dose-area product per unit of fluoro time:" << " "
        <<*average_DAP_per_FluoroTime << " (Gy\u00b7cm\u00b2)/min" << endl
     << "Average air kerma per unit of fluoro time:" << " "
        <<*average_AK_per_FluoroTime << " mGy/min" << endl
     << "Average dose-area product per unit of procedure time:" << " "
        <<*average_DAP_per_ProcedureTime << " (Gy\u00b7cm\u00b2)/min" << endl
     << "Average air kerma per unit of procedure time:" << " "
        <<*average_AK_per_ProcedureTime << " mGy/min" << endl
     << '\n' << '\n' <<'\n'
     << "**********Standard Deviations**********" << endl
     << '\n'
     << "Standard deviation of height:" << " " << *stdev_height << " cm" << endl
     << "Standard deviation of weight:" << " " << *stdev_weight << " kg" << endl
     << "Standard deviation of contrast volume:" << " " << *stdev_contrast << " ml" << endl
     << "Standard deviation of fluoro time:" << " " << *stdev_fluoro_time << " min" << endl
     << "Standard deviation of dose-area product:" << " " << *stdev_DAP << " Gy\u00b7cm\u00b2" << endl
     << "Standard deviation of air kerma:" << " " << *stdev_AirKerma << " mGy" << endl
     << "Standard deviation of procedure time:" << " " << *stdev_ProcedureTime << " min" << endl
     << "Standard deviation of dose-area product per unit of fluoro time:" << " "
        <<*stdev_DAP_per_FluoroTime << " (Gy\u00b7cm\u00b2)/min" << endl
     << "Standard deviation of air kerma per unit of fluoro time:" << " "
        <<*stdev_AK_per_FluoroTime << " mGy/min" << endl
     << "Standard deviation of dose-area product per unit of procedure time:" << " "
        <<*stdev_DAP_per_ProcedureTime << " (Gy\u00b7cm\u00b2)/min" << endl
     << "Standard deviation of air kerma per unit of procedure time:" << " "
        <<*stdev_AK_per_ProcedureTime << " mGy/min" << endl
        << '\n' << '\n' <<'\n'
     << "**********Standard Errors of the Mean Values**********" << endl
     << '\n'
     << "Standard error of height:" << " " << *stderr_height << " cm" << endl
     << "Standard error of weight:" << " " << *stderr_weight << " kg" << endl
     << "Standard error of contrast volume:" << " " << *stderr_contrast << " ml" << endl
     << "Standard error of fluoro time:" << " " << *stderr_fluoro_time << " min" << endl
     << "Standard error of dose-area product:" << " " << *stderr_DAP << " Gy\u00b7cm\u00b2" << endl
     << "Standard error of air kerma:" << " " << *stderr_AirKerma << " mGy" << endl
     << "Standard error of procedure time:" << " " << *stderr_ProcedureTime << " min" << endl
     << "Standard error of dose-area product per unit of fluoro time:" << " "
        <<*stderr_DAP_per_FluoroTime << " (Gy\u00b7cm\u00b2)/min" << endl
     << "Standard error of air kerma per unit of fluoro time:" << " "
        <<*stderr_AK_per_FluoroTime << " mGy/min" << endl
     << "Standard error of dose-area product per unit of procedure time:" << " "
        <<*stderr_DAP_per_ProcedureTime << " (Gy\u00b7cm\u00b2)/min" << endl
     << "Standard error of air kerma per unit of procedure time:" << " "
        <<*stderr_AK_per_ProcedureTime << " mGy/min" << endl;

    //Close the output file
    OutFile.close();
}

//Main function
int main()
{

//Declare an instance of a DoseData class object using dynamic memory allocation.
//Because we are creating a pointer to a DoseData object on the heap, we can
//only access DoseData methods using the "->" operator.  If we created DoseData
//normally on the stack, then the "." operator could be used to acess class
//methods instead.
DoseData *test = new DoseData;
//DoseRateData *test2 = new DoseRateData;

////These variables  will store the average value for an array of data.
float average_result;
//
////This variable will store the standard deviation for an array of data.
float standard_dev;
//
////This variable will hold the number of lines that are present in the data file
////and also be used to print out the number of lines.
int number_lines;

//We will now use the copy constructor to create a 2nd dose data object and by
//doing a deep copy of data from "test" into this new object.  This new object
//will also be created on the heap.  For the copy constructor to work, the orginal
//DoseData object "test" needs to be dereferenced (with "*"), since the arguement must be
//converted and sent in as a value first before it can be passed by reference.

OutputDataFile *test2 = new OutputDataFile;
test2->SendToTextFile();

//Use the functions to generate a mean and standard deviation for an array of data.
//Need to use one of the get functions in the DoseData class to access
//protected members.
    average_result = test->average(test->getHeightData());
    standard_dev = test->std_dev(test->getHeightData(), average_result);
    number_lines = test->getNumLines();

//Print the mean and standard deviation values.  Also print the number
//of lines in the file.
     cout << average_result << endl;
     cout << standard_dev << endl;
     cout << number_lines << endl;


//Delete the memory allocated for DoseData object to avoid memory leak.
delete test;
delete test2;

//Assign pointers to NULL value to avoid crashes.
test = NULL;
test2 = NULL;

return 0;
}
