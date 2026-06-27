import argparse, pathlib

parser = argparse.ArgumentParser()

parser.add_argument("-p", "--path")
parser.add_argument("-n", "--name", default="MyProject")

args = parser.parse_args()

project_name = args.name

if args.path is None:
    base_path = pathlib.Path.home() / "BulwarkProjects"
else:
    base_path = pathlib.Path(args.path)

project_path = base_path / project_name

counter = 1
while project_path.exists():
    project_path = base_path / f"{project_name}{counter}"
    counter += 1

project_path.mkdir(parents=True)
