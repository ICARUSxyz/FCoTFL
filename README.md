# FCoTFL
This repository provides a framework for **FCoTFL: Formal Chain-of-Thought prompting for Software Fault localization** using Large Language Models (LLMs).   It integrates several benchmark datasets (Defects4J, QuixBugs, and an unseen dataset), formal specifications (SOFL), and prompt-based LLM workflows.

---

## 1. Project Description
This repository contains:
- The **Datasets** used in our experiments.
- The **Large Language Models** used in our experiments.
- The **Results** of the experiments.

Our research introduces **Formal Specification** into **Chain-of-Thought prompting** to enhance **Software Fault Localization (FL)**.
---

## 2. Directory Structure

```

├── Datasets/
│   ├── D4J/                        # Defects4J dataset
│   │   ├── Codes/                  # buggy (b) and fixed (f) versions
│   │   ├── Locations/              # buggy line annotations
│   │   ├── SOFL/                   # SOFL specifications
│   │   ├── BugSymptoms/              # bug reports 
│   ├── QuixBugs/                   # QuixBugs dataset
│   │   ├── Codes/                  # Java buggy & correct implementations
│   │   ├── Locations/              # buggy line annotations
│   │   ├── SOFL/                   # SOFL specifications
│   │   ├── BugSymptoms/              # bug reports
│   ├── UnseenCode-FL/              # Student-written unseen dataset
│   │   ├── Codes/
│   │   ├── Locations/
│   │   ├── SOFL/
│   │   ├── Prompt/                 # Prompt files for running LLM
│   │   ├── BugSymptoms/
├── LLM/
│   ├── GPT/                        # GPT-based runner
│   ├── OpenSource/                 # Open-source model runner
├── Results/                        # raw experimental results
├── requirements.txt
└── README.md

````

---

## 3. Datasets

This repo builds on widely-used FL datasets:

- **[Defects4J](https://github.com/rjust/defects4j)**  
  - A benchmark with real-world Java bugs from projects such as Chart, Lang, Math, and Time.
  - Provides buggy/fixed program versions.

- **[QuixBugs](https://github.com/jkoppel/QuixBugs)**  
  - A dataset of 40 small algorithmic problems, each containing a buggy and a fixed Java implementation.
  - Includes reference test cases.

- **UnseenCode-FL**  
  - A newly constructed dataset of 70 buggy programs (multi-line errors), unseen by training models.
  - Contains buggy/fixed code, buggy line locations, SOFL specs, prompts, and bug reports.

---

## 4. LLM Runners

Two simple Python scripts are provided to run prompts against different types of models:

###  GPT Models

File: `LLM/GPT/run_prompts_gpt.py`

Configuration (inside the script):
```python
MODEL = "gpt-5"      # or "gpt-4o", "gpt-4-turbo"
OPENAI_API_KEY = "your openai key"  # replace with your key
```

Run:

```
python LLM/GPT/run_prompts_gpt.py
```

###  Open-Source Models 

File: `LLM/OpenSource/run_prompts_open_source.py`

Configuration (inside the script):

```python
# Default
MODEL = "deepseek-ai/deepseek-coder-v2-16b-base"
# Alternatives:
# MODEL = "bigcode/starcoder2-15b"
# MODEL = "meta-llama/CodeLlama-34b-Instruct-hf"
```

Run:

```
python LLM/OpenSource/run_prompts_open_source.py
```

---

## 5. Requirements

Install dependencies:

```
pip install -r requirements.txt
```

Main dependencies:
```
openai==1.2.0
torch==2.1.0
transformers==4.35.0
accelerate==0.22.0
```
---

## 6. Result
The raw experimental results are available under the `Results/` directory for reference.

## License
- Code: Apache-2.0 (see `LICENSE`)
- Textual contents (docs, SOFL specs, prompt templates) and experiment artifacts (figures, CSVs that are ours): CC BY 4.0 (see `LICENSE-CC-BY-4.0`)
- Third-party datasets/code (e.g., Defects4J, QuixBugs) are not redistributed; please follow their original licenses. We provide scripts to fetch them.
