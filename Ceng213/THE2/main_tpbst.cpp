#include <iostream>

#include "tpbst.hpp"

int main() {
  TwoPhaseBST<int> tpbst;

  tpbst.print()
          .print("ceng213")
          .print("ceng213", "sec1")
          .insert("ceng213", "sec2", 26)
          .insert("ceng213", "sec1", 25)
          .insert("ceng213", "sec3", 24)
          .insert("ceng477", "sec2", 50)
          .insert("ceng477", "sec1", 49)
          .print()
          .print("ceng213")
          .print("ceng477")
          .print("ceng213", "sec1")
          .print("ceng477", "sec1")
          .remove("ceng213", "sec2")
          .remove("ceng477", "sec2")
          .print();
   std::cout << "Number of enrolled students in ceng213 - sec3 is " << *(tpbst.find("ceng213", "sec3")) << std::endl;

  return 0;
            //.print("ceng213")
            //.print("ceng213", "sec1")

                  /*  .insert("ceng213", "sec2", 26)
                    .insert("ceng213", "sec1", 25)
                    .insert("ceng213", "sec3", 24)
                    .insert("ceng477", "sec2", 50) */
              //      .print();
        //    tpbst.insert("ceng213","i",272);
        //    tpbst.insert("ceng213","f",273);
        //    tpbst.insert("ceng213","g",274);
        //    tpbst.insert("ceng213","c",275);

      //      tpbst.insert("ceng477", "sec2", 50);
          //  tpbst.insert("ceng477", "sec1", 49);
          //  tpbst.insert("ceng476", "sec1", 49);
          //  tpbst.insert("ceng111", "sec2", 49);
        //    tpbst.print("ceng213");
        //    std::cout << "-------------" << std::endl;
      //      tpbst.print();
        //    .print("ceng477")
        //    .print("ceng213", "sec1")
        //    .print("ceng477", "sec1")
        //   tpbst.remove("ceng213", "j");
        //    tpbst.print("ceng213");
        //    tpbst.print("ceng213");
        //    .remove("ceng477", "sec2")
        //    .print();
  //  std::cout << "Number of enrolled students in ceng213 - sec3 is " << *(tpbst.find("ceng213", "sec3")) << std::endl;

}
