#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <matrixlib.hpp>


glm::vec4 translate(glm::vec4 position, glm::vec3 translateXYZ){
    glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), translateXYZ);
    return translateMatrix * position;
}
