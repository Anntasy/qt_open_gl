#include "rend.h"
#include "h.h"

Rend::Rend(): QQuickFramebufferObject::Renderer() { // FBO
    all_data = new AllData();
    m_program = new QOpenGLShaderProgram();
    camera = new OurCamera();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex_shader.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment_shader.frag");
    m_program->link();
    set_picture();
}

Rend::~Rend()
{
    delete all_data;
    delete m_program;
    delete camera;
}

QOpenGLFramebufferObject* Rend::createFramebufferObject(const QSize &size)
{
    initializeOpenGLFunctions();
    QOpenGLFramebufferObjectFormat format;
    int smooth = 0;

    format.setAttachment(QOpenGLFramebufferObject::Depth);
    format.setSamples(smooth);
    format.setInternalTextureFormat(GL_RGBA8);
    // format.setTextureTarget(GL_TEXTURE_2D);

    q_size = size;
    return new QOpenGLFramebufferObject(size, format);
}

void Rend::synchronize(QQuickFramebufferObject* t)
{
    auto * it = static_cast<FBO*>(t);
    q_angle  = it->get_angle();
}

void Rend::set_picture() // FBO
{
    all_data->add_triangle(0.25f, 0.25f, 1.0f, 0.25f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
    all_data->add_cube({-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}, {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.1f});
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    all_data->init(f);
}

void Rend::render()
{
    initializeOpenGLFunctions();
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    glViewport(0, 0, q_size.width(), q_size.height());

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    m_program->bind();
    all_data->vao.bind();


    QMatrix4x4 view = camera->get_view();
    QMatrix4x4 projection;
    projection.perspective(glm::radians(45.0f), HEIGHT/WIDTH, 0.05f, 50.0f);

    QMatrix4x4 transformation;

    int start_i = 0;
    glActiveTexture(GL_TEXTURE0);
    all_data->tex1->bind();
    m_program->setUniformValue("texture_sample1", 0);


    for (int i=0; i<all_data->count_obj; i++)
    {
        QMatrix4x4 model_obj;
        model_obj.translate(toQVector3D(all_data->models[i]));
        transformation = projection*view*model_obj;

        m_program->setUniformValue("transformation", transformation);

        glDrawElements(GL_TRIANGLES, all_data->identify[i]*3, GL_UNSIGNED_INT, (void *)(start_i));
        start_i += all_data->identify[i]*sizeof(Element);
    }
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void *)0);
    all_data->vao.release();
    m_program->release();
    all_data->tex1->release();

    update();
}
