#include <iostream>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <sstream>

namespace py = pybind11;


int add(int i, int j) {
    return i + j;
}
double pow1(const double& x, const unsigned int n) {
    if (n == 0) {
        return 1.0;
    }
    return x * pow1(x, n - 1);
}


struct Quaternion {
    double _w;
    double _x;
    double _y;
    double _z;

    Quaternion(const double w, const double x, const double y, const double z):_w(w),_x(x),_y(y),_z(z) {

    }

    Quaternion quaternion_mul(const Quaternion& autre) {
        return Quaternion(
            _w*autre._w - (_x*autre._x +_y*autre._y + _z*autre._z),
            _w*autre._x + _x*autre._w + _y * autre._z - _z * autre._y,
            _w*autre._y + _y*autre._w + _z * autre._x - _x * autre._z,
            _w*autre._z + _z*autre._w + _x * autre._y - _y * autre._x
        );
    }

    Quaternion operator+(const Quaternion& qautre){
        return Quaternion(_w+ qautre._w,_x+ qautre._x,_y+ qautre._y,_z+ qautre._z);
    }

    std::array<double,3> imagPur() const{
      return {_x,_y,_z};
    }


    friend std::ostream& operator<<(std::ostream& flux, const Quaternion& q1);
};

Quaternion conjugate(const Quaternion& quat){
    return Quaternion(quat._w,-quat._x,-quat._y,-quat._z);
}

std::ostream& operator<<(std::ostream& flux, const Quaternion& q1){
    flux << "quat("<<q1._w<<","<<q1._x<<","<<q1._y<<","<<q1._z<<")";
    return flux;
}





template<typename T>
struct GrayPixel {
    T _val;

public:
    GrayPixel(const T valG = 0) :_val(valG) {
    }
    std::string to_string() const {
        return std::to_string(_val);
    }

    T getValue() const {
        return _val;
    }

};
template<typename PixelType>
struct Image{
    const size_t _largeur;
    const size_t _hauteur;
    std::vector<PixelType> _pixels;

    Image(const size_t largeur, const size_t hauteur):_largeur(largeur),_hauteur(hauteur),_pixels(largeur*hauteur,PixelType()){        
    }

    PixelType getPixel(const int l, const int c) const{
        return _pixels.at(l*_largeur + c);
    }

    void setPixel(const int l, const int c, const PixelType& autrePixel){
        _pixels[l*_largeur + c] = autrePixel;
    }


    void setImgLine(const int l, const PixelType& autrePixel){
        for(size_t c = 0 ; c<_largeur ; ++c )
            setPixel(l,c,autrePixel);
    }


    std::string to_string() const{
        std::string contenuImage("");
        for(size_t i = 0 ; i<_hauteur ; ++i){
            for(size_t j = 0 ; j<_largeur ; ++j){
                contenuImage += getPixel(i,j).to_string() + " ";
            }
            contenuImage += "\n";
        }
        return contenuImage;
    }

    template<typename PixelType2>
    friend std::ostream& operator<<(std::ostream& os, const Image<PixelType2>& img );

};

std::vector<std::vector<int>> imgDegradee(const Image<GrayPixel<int>>& img) {
    std::vector<std::vector<int>> imgSortie;
    for (size_t i = 0; i < img._hauteur; ++i) {
        std::vector<int> ligne;
        for (size_t j = 0; j < img._largeur; ++j) {
            ligne.push_back(i*255/(img._hauteur-1));
        }
        imgSortie.push_back(ligne);
    }
    return imgSortie;
}


std::vector<std::vector<int>> imgDegradeeEtSeuillage(const Image<GrayPixel<int>>& img, const int seuil) {
    std::vector<std::vector<int>> imgSortie = imgDegradee(img);

    for(int i = 0 ; i< imgSortie.size();++i){
        for(int j=0;j<imgSortie[0].size();++j){
            if(imgSortie[i][j] > seuil){
                imgSortie[i][j] = 255;
            }
            else{
                imgSortie[i][j] = 0;
            }
        }
    }


    return imgSortie;
}



PYBIND11_MODULE(pybind11testwin, m) {
m.doc() = "pybind11 example test"; // optional module docstring
// m.def("pow", &pow1, "A function that computes a pow b");
// m.def("add", &add, "A function that adds two numbers");

py::class_<Image<GrayPixel<int>>>(m,"Grayimage")
    .def(py::init<const int &, const int&>())
    .def("__repr__",[](const Image<GrayPixel<int>> img){
        return img.to_string();
    })
    .def("getPixel",[](const Image<GrayPixel<int>> img, const int i, const int j){
        return img.getPixel(i,j).getValue();
    })
    .def("imageDegrade",[](const Image<GrayPixel<int>> img){
        return imgDegradee(img);
    })
    .def("binarisation",[](const Image<GrayPixel<int>> img, const int seuil ){
        return imgDegradeeEtSeuillage(img, seuil);
    });

    // py::class_<Quaternion>(m, "Quat")
    //     .def(py::init<const double &,const double &,const double &,const double &>())
    //     .def("__repr__", [](const Quaternion& q){
    //         std::stringstream strStream;
    //         strStream << q;
    //         return strStream.str();
    //     })
    //     .def("__add__", [](Quaternion a, Quaternion b) {
    //         return a + b;
    //     }, py::is_operator())
    //     .def("__mul__", [](Quaternion a, const Quaternion& b) {
    //         return a.quaternion_mul(b);
    //     }, py::is_operator())
    //     .def("conju",[](const Quaternion& a){
    //         return conjugate(a);
    //     })
    //     .def("getImag",[](const Quaternion& q){
    //         return q.imagPur();
    //     });
}