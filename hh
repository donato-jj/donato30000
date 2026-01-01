from PySide6.QtWidgets import *
from PySide6.QtCore import *
from PySide6.QtGui import *
import random, sys, webbrowser


# ----------------------------------------------------------
#   CENTRO EDUCATIVO DE INTELIGENCIA ARTIFICIAL
#   APRENDE CON DONATO CONTURLA
# ----------------------------------------------------------

APP_URL = "https://tu-dominio-oficial.com"   # -----> aquí pones tu URL real cuando la alojes


class AIEducativa(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("CENTRO EDUCATIVO DE INTELIGENCIA ARTIFICIAL – APRENDE CON DONATO CONTURLA")
        self.setMinimumSize(1000, 700)

        # Estilo futurista
        self.setStyleSheet("""
            QMainWindow { background-color: #0d1117; }
            QLabel { color: white; font-size: 16px; }
            QTextEdit, QPlainTextEdit {
                background-color: #0d0f14;
                color: #00ffc6;
                border: 2px solid #3a3f47;
                border-radius: 10px;
                padding: 10px;
            }
            QPushButton {
                background-color: #00ffc6;
                color: black;
                font-weight: bold;
                font-size: 16px;
                border-radius: 12px;
                padding: 8px;
            }
            QPushButton:hover { background-color: #04c29e; }
            QComboBox {
                background-color: #0d0f14;
                color: #00ffc6;
                border: 2px solid #3a3f47;
                border-radius: 10px;
                padding: 8px;
            }
            QListWidget {
                background-color: #0d0f14;
                color: #7affff;
                border: 2px solid #3a3f47;
                border-radius: 10px;
            }
        """)

        self.interface()

    def interface(self):
        central = QWidget()
        layout = QVBoxLayout()

        titulo = QLabel("CENTRO EDUCATIVO DE INTELIGENCIA ARTIFICIAL – APRENDE CON DONATO CONTURLA")
        titulo.setAlignment(Qt.AlignCenter)
        titulo.setStyleSheet("font-size: 22px; font-weight: bold; color:#00ffc6;")

        subtitulo = QLabel("Aprende IA con Donato Conturla")
        subtitulo.setAlignment(Qt.AlignCenter)
        subtitulo.setStyleSheet("font-size: 17px; color:#38f7ff;")

        layout.addWidget(titulo)
        layout.addWidget(subtitulo)

        self.category = QComboBox()
        self.category.addItems([
            "Biotecnología",
            "Inteligencia Artificial",
            "Big Data",
            "Aprendizaje Automático",
            "Python para IA",
            "Algoritmos de IA",
            "Futuro de la Inteligencia Artificial"
        ])

        self.question = QTextEdit()
        self.question.setPlaceholderText("Escribe tu pregunta aquí...")

        self.response = QPlainTextEdit()
        self.response.setReadOnly(True)

        self.history = QListWidget()

        btn = QPushButton("GENERAR RESPUESTA")
        btn.clicked.connect(self.generate_ai_response)

        share_btn = QPushButton("COMPARTIR AUTOMÁTICO")
        share_btn.clicked.connect(self.share_menu)

        buttons = QHBoxLayout()
        buttons.addWidget(btn)
        buttons.addWidget(share_btn)

        layout.addWidget(QLabel("Selecciona categoría:"))
        layout.addWidget(self.category)
        layout.addWidget(QLabel("Pregunta del usuario:"))
        layout.addWidget(self.question)
        layout.addLayout(buttons)
        layout.addWidget(QLabel("Respuesta Inteligente de la Plataforma:"))
        layout.addWidget(self.response)
        layout.addWidget(QLabel("Historial de consultas:"))
        layout.addWidget(self.history)

        central.setLayout(layout)
        self.setCentralWidget(central)

    # ---------------- GENERAR RESPUESTA ----------------
    def generate_ai_response(self):
        categoria = self.category.currentText()
        pregunta = self.question.toPlainText()

        if pregunta.strip() == "":
            self.response.setPlainText("⚠ Escribe una pregunta para obtener una respuesta educativa.")
            return

        respuesta = self.ai_engine(categoria, pregunta)
        self.response.setPlainText(respuesta)

        self.history.addItem(f"[{categoria}] {pregunta}")

    # ---------------- MOTOR IA SIMULADO ----------------
    def ai_engine(self, categoria, pregunta):

        base = f"📚 Categoría: {categoria}\n🧠 Pregunta: {pregunta}\n\n"

        respuestas = {
            "Biotecnología": [
                "La biotecnología usa organismos vivos para crear soluciones médicas, agrícolas y ambientales...",
                "CRISPR, bioinformática y terapias avanzadas son pilares modernos de la biotecnología."
            ],
            "Inteligencia Artificial": [
                "La IA imita capacidades humanas: aprender, razonar, decidir.",
                "Incluye Deep Learning, Machine Learning, NLP, visión artificial y sistemas autónomos."
            ],
            "Big Data": [
                "Big Data analiza grandes volúmenes de datos buscando patrones útiles.",
                "Utiliza Hadoop, Spark y aprendizaje masivo."
            ],
            "Aprendizaje Automático": [
                "ML permite a sistemas aprender sin programación directa.",
                "Incluye aprendizaje supervisado, no supervisado y reforzado."
            ],
            "Python para IA": [
                "Python es clave gracias a TensorFlow, PyTorch y Scikit-Learn.",
                "Ejemplo básico:\n\nimport sklearn\nprint('IA con Python funcionando!')"
            ],
            "Algoritmos de IA": [
                "Algoritmos clave: Redes Neuronales, SVM, KNN, Árboles, Regresiones.",
                "Permiten clasificar, predecir y detectar patrones."
            ],
            "Futuro de la Inteligencia Artificial": [
                "La IA transformará medicina, educación, transporte y comunicación.",
                "El futuro apunta a IA ética, segura y responsable."
            ]
        }

        resultado = random.choice(respuestas.get(categoria, ["Pronto tendré más información sobre este tema."]))
        return base + resultado + "\n\n👨‍🎓 Aprende IA con Donato Conturla"

    # ---------------- SISTEMA COMPARTIR PROFESIONAL ----------------
    def share_menu(self):
        menu = QMessageBox()
        menu.setWindowTitle("Compartir Automáticamente")
        menu.setText("Selecciona dónde compartir la aplicación educativa IA de Donato Conturla")
        menu.setIcon(QMessageBox.Information)

        menu.addButton("WhatsApp", QMessageBox.AcceptRole)
        menu.addButton("Telegram", QMessageBox.AcceptRole)
        menu.addButton("Facebook", QMessageBox.AcceptRole)
        menu.addButton("Ver URL Oficial", QMessageBox.AcceptRole)

        option = menu.exec()

        if option == 0:
            self.share_whatsapp()
        elif option == 1:
            self.share_telegram()
        elif option == 2:
            self.share_facebook()
        else:
            webbrowser.open(APP_URL)

    def share_whatsapp(self):
        text = f"🔥 Centro Educativo de Inteligencia Artificial – Donato Conturla\nAprende IA, Big Data y Biotecnología\n\nPropietario: Donato Conturla\nCreador IA: Donato Conturla\n\nAccede aquí:\n{APP_URL}"
        webbrowser.open(f"https://wa.me/?text={text}")

    def share_telegram(self):
        webbrowser.open(f"https://t.me/share/url?url={APP_URL}&text=Aprende IA con Donato Conturla")

    def share_facebook(self):
        webbrowser.open(f"https://www.facebook.com/sharer/sharer.php?u={APP_URL}")


# ---------------- EJECUCIÓN ----------------
app = QApplication(sys.argv)
window = AIEducativa()
window.show()
sys.exit(app.exec())
