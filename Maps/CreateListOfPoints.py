import pandas as pd

""" REPLACE THE PATHS!!! """

# Paths to your CSV files
path150 = "/Users/oliverheisel/Documents/GitHub/Lakezone_Geofence/Maps/ListOfPoints/LakeZurich-150m_Vertics_WGS84_SmallArea.csv"
path300 = "/Users/oliverheisel/Documents/GitHub/Lakezone_Geofence/Maps/ListOfPoints/LakeZurich-300m_Vertics_WGS84_SmallArea.csv"


def process_polygon_data(path, polygon_size):
    # Read the CSV file using pandas
    data = pd.read_csv(path)

    # Assuming 'x' and 'y' values are in columns named 'x' and 'y'
    # You may need to replace 'x' and 'y' with the actual column names or indices
    """ Check your data! Maybe you need to change the columns """

    if 'x' in data.columns and 'y' in data.columns:
        x_values = data['x'].dropna().apply(lambda x: round(float(x), 10))
        y_values = data['y'].dropna().apply(lambda y: round(float(y), 11))

        # Convert lists to the desired format
        x_values_str = "{" + ", ".join(x_values.astype(str)) + "}"
        y_values_str = "{" + ", ".join(y_values.astype(str)) + "}"

        print(f"All points for the {polygon_size} Polygon")
        print("X values:", x_values_str)
        print(f"Count of X values: {len(x_values)}")
        print("Y values:", y_values_str)
        print(f"Count of Y values: {len(y_values)}")
    else:
        print(f"Error: 'x' and 'y' columns not found in {path}")


# Process each polygon
process_polygon_data(path150, '150m')
process_polygon_data(path300, '300m')
