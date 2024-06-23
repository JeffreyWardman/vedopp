#pragma once

#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>

typedef vtkSmartPointer<vtkActor> Actor;
typedef vtkSmartPointer<vtkPoints> Vertices;
typedef vtkSmartPointer<vtkCellArray> Cells;
typedef vtkSmartPointer<vtkPolyData> Dataset;
typedef vtkSmartPointer<vtkPolyDataMapper> DatasetMapper;
typedef vtkSmartPointer<vtkMatrix4x4> Matrix4x4;
typedef vtkSmartPointer<vtkTransform> Transform;
typedef vtkSmartPointer<vtkImageData> Image;
// typedef vtkSmartPointer<vtkDataArray> DataArray;

constexpr float EPSILON4 = 0.0001;