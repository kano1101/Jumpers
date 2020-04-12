#include "GameObject.h"

#include "Framework.h"

 // template<class B, class I, class V, class G>
 // void GameObject<B, I, V, G>::Del()
void MainActor::Test()
 {
   // Creator<MainActor>::Destroy(this);
   Creator<MainActor>::Create(pos_.X()-20.0f);
 }
// void GameObject<B, I, V, G>::Test()
// {
//   Creator<MainActor>::Create(count_/50);
// }
