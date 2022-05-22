# Project Overview

This project was a collaboration between Giulio Duregon, Jonah Potzobutt, and Joby George. For detailed methodology, model analysis, and metric evaluation please refer to the report folder. Below are instructions on how to run the code on NYU's HPC cluster.

## Getting Started

After connecting to NYU's HPC, navigate to the directory with this repository and run `source setup.sh` in the terminal. Then add the MovieLens datasets to your `hdfs` filesystem. They must follow this naming convention: `<dataset_size>-<file_name>.csv`. For example: `large-movies.csv`. Make sure to configure necessary filepaths in the `code/constants.py` file.

To create Training, Validation, and Test splits run the `make__splits.py` file. If you need to access the splits in your `hdfs` filesystem, they are named with the following convention: `<dataset_size>-<name_of_set>` For example, `small-train.csv`. Training is named differently depending on model type, for example `"als-small-train.csv"`.

To train and evaluate the ALS or Baseline Recommendation System models on validation splits, use `run_model.py`. Results will be saved in a `.txt` file specified in `code/constants.py`.

## Spark Execution on the Cluster

How to execute make_splits.py:

> spark-submit make_splits.py `dataset_size` `model_type`

For example:

> spark-submit make_splits.py small

How to execute run_model.py in the cluster:

> spark-submit run_model.py `dataset_size` `model_type` `param_dict`

For Example:

> spark-submit run_model.py small als '{"rank":5, "maxIter":5,"regParam":0.05}'
> spark-submit run_model.py large baseline '{"bias":100}'

Make sure the param dict is in single quotes so that the dictionary arguments can be parsed correctly.

## Dependencies

PySpark, Annoy, and LensKit must be installed. See `report` for installation instructions.

## Helpful Commands for the Cluster

### HFS

- Add files to hadoop cluster

> hfs -put

- List files on Hadoop Cluster

> hfs -ls

- Remove Files on Hadoop Cluster

> hfs -rm -r `file_name`

## Yarn Logs

- Access Yarn Logs

> yarn logs -applicationId `application_id` -log_files stdout

## Spark

- Submit Job

> spark-submit `some_script.py` `args`

- Long way to Submit Job (Recommended)

> spark-submit --conf  spark.dynamicAllocation.enabled=true --conf spark.shuffle.service.enabled=false --conf spark.dynamicAllocation.shuffleTracking.enabled=true  `some_script.py` `args`
