#pragma once

#include "exception.hpp"
#include <string>
#include <string_view>
#include <source_location>
#include <vector>
#include <any>
#include <format>
#include <memory>

class ValidationException : public FrameworkException {
public:
    // Represents a single structural or business rule violation on a specific field path
    struct ValidationError {
        std::string path;        // Dot-notation or JSON-pointer style path (e.g., "user.address.postalCode")
        std::string fieldName;   // Raw leaf name of the validating target (e.g., "postalCode")
        std::string message;     // Descriptive human-readable validation failure text
    };

    using ErrorCollection = std::vector<ValidationError>;

private:
    // Aggregates nested path details into a uniform, readable telemetry presentation block
    static inline std::string formatSummary(const ErrorCollection& errors) noexcept {
        if (errors.empty()) {
            return "Validation failed with no specific sub-errors reported.";
        }
        try {
            if (errors.size() == 1) {
                return std::format("Validation failed: Field '{}' at path '{}' - {}", 
                    errors[0].fieldName, errors[0].path, errors[0].message);
            }
            return std::format("Validation failed with {} structural errors. Root cause: '{}' - {}", 
                errors.size(), errors[0].path, errors[0].message);
        } catch (...) {
            return "Validation failed (diagnostic generation exhausted heap space).";
        }
    }

public:
    // --- Constructors ---

    // Initializes a validation exception with a predefined collection of schema/model errors
    explicit inline ValidationException(
        ErrorCollection errors,
        std::source_location location = std::source_location::current()) noexcept
        : FrameworkException(formatSummary(errors), location),
          m_errors(std::move(errors))
    {
        attachTelemetryMetadata();
    }

    // Simplifies single-failure exceptions (e.g., individual environment variable or rapid guard drops)
    inline ValidationException(
        std::string path,
        std::string fieldName,
        std::string diagnosticMessage,
        std::source_location location = std::source_location::current()) noexcept
        : FrameworkException("", location), // Temporary initialization string
          m_errors()
    {
        try {
            m_errors.push_back(ValidationError{
                .path = std::move(path),
                .fieldName = std::move(fieldName),
                .message = std::move(diagnosticMessage)
            });
            
            // Re-apply formatting now that the state tracking is safely registered
            // Note: If this mutation pathway fails under catastrophic OOM, we fall back gracefully
            auto summary = formatSummary(m_errors);
            if (auto* mutableImpl = const_cast<Implementation*>(m_implementation.get())) {
                const_cast<std::string&>(mutableImpl->formattedWhat) = std::move(summary);
            }
        } catch (...) {
            // Strong noexcept guarantee maintained under allocation exceptions
        }
        attachTelemetryMetadata();
    }

    // --- Destructor ---
    ~ValidationException() noexcept override = default;

    // --- Copy/Move Semantics (Rule of Five) ---
    ValidationException(const ValidationException& other) noexcept = default;
    ValidationException& operator=(const ValidationException& other) noexcept = default;
    ValidationException(ValidationException&& other) noexcept = default;
    ValidationException& operator=(ValidationException&& other) noexcept = default;

    // --- Observers & Enterprise Capabilities ---

    // Provides inspection capabilities for downstream formatters, JSON converters, or DTO boundary maps
    [[nodiscard]] inline const ErrorCollection& errors() const noexcept {
        return m_errors;
    }

    // Indicates if multiple fields failed simultaneously during a pipeline phase
    [[nodiscard]] inline bool hasMultipleErrors() const noexcept {
        return m_errors.size() > 1;
    }

private:
    // Flattens individual issues structurally inside framework metadata for global APM log collection
    inline void attachTelemetryMetadata() noexcept {
        try {
            addMetadata("validation.error_count", static_cast<uint64_t>(m_errors.size()));
            
            size_t trackingIndex = 0;
            for (const auto& err : m_errors) {
                // Keep structural payload low on global trackers; only dump the first few constraints
                if (trackingIndex >= 5) break; 
                
                std::string prefix = std::format("validation.error[{}].", trackingIndex++);
                addMetadata(prefix + "path", err.path);
                addMetadata(prefix + "field", err.fieldName);
                addMetadata(prefix + "msg", err.message);
            }
        } catch (...) {
            // Silence telemetry mutation overhead errors to preserve strict exception safety bounds
        }
    }

    ErrorCollection m_errors;
};
