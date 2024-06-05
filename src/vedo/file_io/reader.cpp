#include "reader.h"

#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>

#include <stdexcept>
#include <string_view>

#include "../errors.h"
#include "../types.h"
#include "helpers.h"

namespace vedo::file_io::reader
{
    Dataset load(std::string_view filename)
    {
        Dataset dataset;
        if (filename.ends_with(".stl"))
        {
            auto reader = vtkSmartPointer<vtkSTLReader>::New();
            reader->SetFileName(filename.data());
            reader->Update();
            dataset = reader->GetOutput();
        }
        else if (filename.ends_with(".ply"))
        {
            auto reader = vtkSmartPointer<vtkPLYReader>::New();
            reader->SetFileName(filename.data());
            reader->Update();
            dataset = reader->GetOutput();
        }
        else if (filename.ends_with(".obj"))
        {
            auto reader = vtkSmartPointer<vtkOBJReader>::New();
            reader->SetFileName(filename.data());
            reader->Update();
            dataset = reader->GetOutput();
        }
        else
        {
            throw vedo::errors::UnsupportedFileTypeException("Unsupported file type: " + std::string(getFileExtension(filename)));
        }

        return dataset;
    }
}  // namespace vedo::file_io::reader